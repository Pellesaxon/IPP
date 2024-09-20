#include <iostream>
#include <vector>
#include <thread>
#include <functional>
#include <mutex>
#include <cmath>
#include <string>
#include <chrono>
#include <vector>


std::vector<int> initial_primes(int max, std::vector<bool> &is_prime) { //compute initial primes first up to sqrt(max) (sequentially), because they are used for parallel part
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

void thread_primes(int start, int end, const std::vector<int>& init_primes, std::vector<bool>& is_primes) { //the threads compute primes on their local vector
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

    auto start_time = std::chrono::high_resolution_clock::now(); //start time here??

    std::vector<bool> is_prime(max + 1, true);
    is_prime[0] = is_prime[1] = false;
    std::vector<int> init_primes = initial_primes(max, is_prime);

    int range_start = static_cast<int>(std::sqrt(max)) + 1;
    int range_length = max - range_start + 1;
    int chunk_size = range_length/ num_threads;


    std::thread *t = new std::thread[num_threads];

    for (int i = 0; i < num_threads; ++i) {
        int start = range_start + i * chunk_size;
        int end = (i == num_threads - 1) ? max : start + chunk_size - 1;

        t[i] = std::thread(thread_primes, start, end, std::cref(init_primes), std::ref(is_prime));
    }

    for (int i=0; i<num_threads; ++i)
    {
      t[i].join();
    }

    auto end_time = std::chrono::high_resolution_clock::now(); //where we end the time, makes sense i think??

    std::chrono::duration<double> elapsed = end_time - start_time;
    std::cout << "Time: " << elapsed.count() << " seconds" << std::endl;

    //for validation
    int n_primes = 0;
    for (int i=0; i <= max; i++){
        
        if (is_prime[i]) {
            n_primes++;
        }
    }
    std::cout << "Number of primes up to " << max << " is " << n_primes <<std::endl;

    return 0;
}
