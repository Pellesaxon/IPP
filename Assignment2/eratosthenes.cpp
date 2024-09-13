#include <iostream>
#include <vector>
#include <thread>
#include <functional>
#include <mutex>
#include <cmath>
#include <string>
#include <chrono>
#include <vector>

std::mutex mutex;


void thread_primes(int start,int end) {
    
    // create local_is_prime storage using start and end (could be empty vecotr?    )
    // call eratosthenes on local_is_prime
    // try to use lock to write local_is_prime to is_prime ELSE continue computing ertosthenes || just be done and hand to master?
    return ;
    
}

std::vector<bool> eratosthenes(int start, int max, std::vector<bool> is_prime ) { //max should be end?
    //change k to a lower bound?
    for (int k = start; k * k <= max; ++k) {
        if (is_prime[k]) {
            for (int multiple = k * k; multiple <= max; multiple += k) {
                is_prime[multiple] = false;
            }
        }
    }
    return is_prime;
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
    auto start_time = std::chrono::high_resolution_clock::now();

    std::vector<bool> is_prime(max + 1, true);
    is_prime[0] = is_prime[1] = false;
    int sqrt_max = static_cast<int>(std::sqrt(max));

    int range_start = static_cast<int>(std::sqrt(max)) + 1;
    int range_length = max - range_start + 1;
    int chunk_size = range_length / num_threads;


    std::vector<std::thread> threads;

    

    std::vector<bool> initial_primes = eratosthenes(2, sqrt_max, is_prime);



    for (int i = 0; i < num_threads; ++i) {
        int start = range_start + i * chunk_size;
        int end = (i == num_threads - 1) ? max : start + chunk_size - 1;


        threads.emplace_back(eratosthenes, start, end, max);
    }




    for (auto &t : threads) {
        t.join();
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end_time - start_time;

    std::cout << "Time: " << elapsed.count() << " seconds" << std::endl;

    return 0;
}
