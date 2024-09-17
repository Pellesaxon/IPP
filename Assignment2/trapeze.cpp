#include <iostream>
#include <vector>
#include <thread>
#include <functional>
#include <mutex>
#include <cmath>
#include <string>
#include <chrono>

std::mutex mutex;

double func(double x) {
    
    return 4 / (1 + x * x);
}

double trapeze_rule(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.5 * (func(a) + func(b));
    for (int i = 1; i < n; ++i) {
        sum += func(a + i * h);
    }
    return sum * h;
}


void integrate(double a, double b, int n, double &result) {
    double local_result = trapeze_rule(a, b, n);
    mutex.lock();
    //dis is da critical zection yao
    result += local_result;
    mutex.unlock();
}

void print_help() {
    std::cout << "Usage: integrate [options]\n"
              << "Options:\n"
              << "  <num_trapezoids>    Number of trapezoids (first argument)\n"
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

    int num_trapezoids = std::stoi(argv[1]);
    int num_threads = std::stoi(argv[2]);

    if (num_threads <= 0 || num_trapezoids <= 0) {
        std::cerr << "Error: Threads and trapezoids must be positive.\n";
        return 1;
    }
    if (num_threads > 64){
        std::cerr << "Error: Yoo bro don't go crazy on the number of threads ok?!.\n";
        return 1;
    }
    auto start_time = std::chrono::high_resolution_clock::now();

    double a = 0.0; 
    double b = 1.0;  
    double result = 0.0;

    std::vector<std::thread> threads;
    int trapezoids_per_thread = num_trapezoids / num_threads;
    double interval_length = (b - a) / num_threads;

    

    for (int i = 0; i < num_threads; ++i) {
        double local_a = a + i * interval_length;
        double local_b = local_a + interval_length;
        int local_trapezoids = (i == num_threads - 1) ? num_trapezoids - (trapezoids_per_thread * (num_threads - 1)) : trapezoids_per_thread;

        threads.emplace_back(integrate, local_a, local_b, local_trapezoids, std::ref(result));
    }

    for (auto &t : threads) {
        t.join();
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end_time - start_time;

    std::cout << "Estimated integral: " << result << std::endl;
    std::cout << "Time: " << elapsed.count() << " seconds" << std::endl;

    return 0;
}
