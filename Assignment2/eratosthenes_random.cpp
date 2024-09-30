#include <iostream>
#include <vector>
#include <thread>
#include <functional>
#include <mutex>
#include <cmath>
#include <string>
#include <chrono>
#include <vector>
#include <algorithm>
#include <random>

//g++ -Wall -std=c++11 -pthread eratosthenes.cpp -o eratosthenes
//g++ -Wall -std=c++11 -pthread eratosthenes_random.cpp -o eratosthenes_random
//chmod +x eratosthenes_sc.sh

std::vector<int> initial_primes(int max, std::vector<int> &is_prime) { //compute initial primes first up to sqrt(max) (sequentially), because they are used for parallel part
    int limit = static_cast<int>(std::sqrt(max));
    std::vector<int> init_primes;

    for (int k = 2; k <= limit; ++k) {
        if (is_prime[k] != 0) {
            init_primes.push_back(k);
            for (int multiple = k * k; multiple <= limit; multiple += k) {
                is_prime[multiple] = 0;
            }
        }
    }
    return init_primes;
}

void thread_primes(int start, int end, const std::vector<int>& init_primes, std::vector<int>& random_is_prime_shit_idk_man) { //the threads compute primes on their local vector

    for (int p : init_primes) {

        for (int i = start; i <= end; i++) {
            if (random_is_prime_shit_idk_man[i]%p == 0) 
                random_is_prime_shit_idk_man[i] = 0;
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

    auto start_time = std::chrono::high_resolution_clock::now(); //start time


    std::vector<int> random_is_prime_shit_idk_man(max+1);
    for (int i = 0; i <= max; i++){
        random_is_prime_shit_idk_man[i] = i;
    }
    random_is_prime_shit_idk_man[0] = random_is_prime_shit_idk_man[1] = 0;
    std::vector<int> init_primes = initial_primes(max, random_is_prime_shit_idk_man);
    

    int range_start = static_cast<int>(std::sqrt(max)) + 1;
    int range_length = max - range_start + 1;
    int chunk_size = range_length/ num_threads;
    

    //randomize stuff
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng(seed);
    std::shuffle(&random_is_prime_shit_idk_man[range_start], &random_is_prime_shit_idk_man[max], rng);


    //threading
    std::thread *t = new std::thread[num_threads];

    for (int i = 0; i < num_threads; ++i) {
        int start = range_start + i * chunk_size;
        int end = (i == num_threads - 1) ? max : start + chunk_size - 1;

        t[i] = std::thread(thread_primes, start, end, std::ref(init_primes), std::ref(random_is_prime_shit_idk_man));
    }


    for (int i=0; i<num_threads; ++i)
    {
      t[i].join();
    }


    auto end_time = std::chrono::high_resolution_clock::now(); //where we end the time


    std::chrono::duration<double> elapsed = end_time - start_time;
    std::cout << "Time: " << elapsed.count() << " seconds" << std::endl;
    
    int n_primes = 0;
    for (int i=0; i <= max; i++){
        
        if (random_is_prime_shit_idk_man[i] != 0) {
            n_primes++;
        }
    }
    std::cout << "Number of primes up to (and including) " << max << " is " << n_primes <<std::endl;

    return 0;
}
