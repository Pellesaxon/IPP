#include <iostream>
#include <vector>
#include <thread>
#include <functional>
#include <mutex>
#include <cmath>
#include <string>
#include <chrono>
#include <vector>

//not currently used, but if we want to have dynamic partition of data we might need it
std::mutex mutex;




std::vector<int> initial_primes(int max, std::vector<bool> &is_prime) { //compute initial primes first, because they can be used for the threads
    int limit = static_cast<int>(std::sqrt(max));
    is_prime[0] = is_prime[1] = false;
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

void thread_primes(int start, int end, const std::vector<int>& init_primes, std::vector<bool>& is_prime) { //the threads compute primes on their allocated segment of the vector

    for (int p : init_primes) {

    int first_multiple = p * p;
    if (first_multiple < start) {
        if (start % p == 0) {
            first_multiple = start;
        } else {
            first_multiple = start + (p - (start % p));
        }
    }

    for (int multiple = first_multiple; multiple <= end; multiple += p) {
        is_prime[multiple - start] = false;
    }
}
    return;
    
}

void print_help() {
    std::cout << "Usage: integrate [options]\n"
              << "Options:\n"
              << "  <max>    Max number (first argument)\n"
              << "  <num_threads>       Number of threads (second argument)\n"
              << "  -h                  Show this help message\n";
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Error: Incorrect number of arguments.\n";
        print_help();
        return 1;
    }

    
    if (std::string(argv[1]) == "-h" || std::string(argv[2]) == "-h") {
        print_help();
        return 0;
    }
    

    int max = std::stoi(argv[1]);
    int num_threads = std::stoi(argv[2]);

    if (num_threads <= 0 || max <= 0) {
        std::cerr << "Error: Threads and max must be positive.\n";
        return 1;
    }
    if (num_threads > 64){
        std::cerr << "Error: Yoo bro don't go crazy on the number of threads ok?!.\n";
        return 1;
    }
    auto start_time = std::chrono::high_resolution_clock::now();

    std::vector<bool> is_prime(max + 1, true);
    std::vector<int> init_primes = initial_primes(max, is_prime);

    int range_start = static_cast<int>(std::sqrt(max)) + 1;
    int range_length = max - range_start + 1;
    int chunk_size = range_length/ num_threads;


    std::vector<std::thread> threads;

    

    



    for (int i = 0; i < num_threads; ++i) {
        int start = range_start + i * chunk_size;
        int end = (i == num_threads - 1) ? max : start + chunk_size - 1; //edge case for if it is "last" thread


        threads.emplace_back(thread_primes, start, end, std::cref(init_primes),std::ref(is_prime));
    }




    for (auto &t : threads) {
        t.join();
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end_time - start_time;
    std::cout << "Time: " << elapsed.count() << " seconds" << std::endl;

    //for validation
    int n_primes = 0;
    for (int i=2; i <= max; i++){
        
        if (is_prime[i]) {
            n_primes++;
        }
    }
    std::cout << "Number of primes between 2 and " << max << " is " << n_primes <<std::endl;

    return 0;
}
