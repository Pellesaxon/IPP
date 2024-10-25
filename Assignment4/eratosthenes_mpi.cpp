#include <iostream>
#include <vector>
#include <functional>
#include <string>
#include <cmath>
#include <chrono>
#include <mpi.h>


std::vector<int> initial_primes(int max, bool *is_prime) { //compute initial primes first up to sqrt(max) (sequentially), because they are used for parallel part
    int limit = static_cast<int>(std::sqrt(max));
    std::vector<int> init_primes;

    for (int k = 2; k <= limit; ++k) {
        if (is_prime[k]) {
            init_primes.push_back(k);
            for (int multiple = k * k; multiple <= limit; multiple += k) {
                is_prime[multiple] = false;
            }
        }
    }
    return init_primes;
}

void thread_primes(int start, int end, const std::vector<int>& init_primes, bool *is_primes) { 
    for (int p : init_primes) {
        for (int i = start; i <= end; i++) {
            if (i%p == 0) 
                is_primes[i] = false;
        }
    }
    return;
}

void print_help() {
    std::cout << "Usage: integrate [options]\n"
              << "Options:\n"
              << "  <max>    Max number (first argument)\n"
              << "  -h                  Show this help message\n";
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Error: Incorrect number of arguments.\n";
        print_help();
        return 1;
    }
    
    if (std::string(argv[1]) == "-h") {
        print_help();
        return 0;
    }
    
    int max = std::stoi(argv[1]);


    auto start_time = std::chrono::high_resolution_clock::now(); //start time
    bool *is_prime = new bool[max + 1];
    for(int i = 0; i < max +1; i++ ){
        is_prime[i] = true;
    }

    is_prime[0] = is_prime[1] = false;
    std::vector<int> init_primes = initial_primes(max, is_prime);
    

    MPI_Init(&argc, &argv);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    

    int range_start = static_cast<int>(std::sqrt(max)) + 1;
    int range_length = max - range_start + 1;
    int chunk_size;      
    chunk_size = range_length/ size;
    int start = range_start + rank * chunk_size;
    int end = (rank == size - 1) ? max : start + chunk_size - 1;
    
    thread_primes(start, end, init_primes, is_prime);
    

    int MAX_MSG_SIZE = chunk_size+size;
    bool msg[MAX_MSG_SIZE];
    if (rank){
        //save you primes to msg, send msg
        for (int prime_index = 0; prime_index < (end-start); prime_index++){
            msg[prime_index] = is_prime[start+prime_index];
        }
        
        std::cout << "Process " << rank <<" sends msg of size " << (end-start+1) << "\n";
        MPI_Send(msg, end-start+1, MPI_C_BOOL, 0, 0, MPI_COMM_WORLD); //+1 on end-start????
    }
        

    if (!rank){
        MPI_Status status;
        int size_recieved;
        std::cout <<  "entered !rank" << std::endl;
        int prime_index = end+1;
        for (int prosses_rank = 1; prosses_rank < size;prosses_rank++){
            std::cout << "prosses rank:"<<  prosses_rank << std::endl;
            MPI_Recv(msg, MAX_MSG_SIZE, MPI_C_BOOL, prosses_rank, 0, MPI_COMM_WORLD, &status);
            std::cout <<"Recived msg from prosess" << prosses_rank << "\n";
            MPI_Get_count(&status, MPI_C_BOOL, &size_recieved);

            for (int i = 0; i < size_recieved; i++){
                is_prime[prime_index] = msg[i];
                std::cout <<"Compiled is_prime for index: " << prime_index << "\n";
                if (is_prime[start+prime_index]){
                    std::cout << "Process " << prosses_rank <<" thinks that " << prime_index <<" is a prime" << "\n";
                }
                prime_index++;
            }
        }
            
        auto end_time = std::chrono::high_resolution_clock::now(); //where we end the time
        std::chrono::duration<double> elapsed = end_time - start_time;
        std::cout << "Time: " << elapsed.count() << " seconds for " << size << " threads"<< std::endl;

        //for validation
        int n_primes = 0;
        for (int i=0; i <= max; i++){
            if (is_prime[i]) {
                std::cout <<"Prime: " << i << std::endl;
                n_primes++;
            }
        }
        std::cout << "Number of primes up to " << max << " is " << n_primes <<std::endl;
    }
    
    MPI_Finalize();
    return 0;
}
