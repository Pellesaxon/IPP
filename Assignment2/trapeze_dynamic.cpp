// g++ -Wall -std=c++11 -pthread trapeze_dynamic.cpp -o dtrapeze

#include <iostream>
#include <vector>
#include <thread>
#include <functional>
#include <mutex>
#include <cmath>
#include <string>
#include <chrono>

std::mutex mutex_result;
std::mutex mutex_counter;


int atomic_counter(int &counter, int nr_of_tickets){
    mutex_counter.lock();
    int ticket = counter;
    counter++;
    mutex_counter.unlock();
    if (ticket > nr_of_tickets){ //check if it should be <= to, depoends on what i do with nr_of_tickets
        return -1;
    }
    return ticket;
}

double func(double x) {
    return 4 / (1 + x * x);
}

double trapeze_rule(double a, double b, int local_trapezoids) {
    double h = (b - a) / local_trapezoids;
    double sum = 0.5 * (func(a) + func(b));
    for (int i = 1; i < local_trapezoids; ++i) {
        sum += func(a + i * h);
    }
    return sum * h;
}

void integrate(double a, double b, int n, double &result) {
    double local_result = trapeze_rule(a, b, n);
    mutex_result.lock();
    //dis is da critical zection yao
    result += local_result;
    mutex_result.unlock();
}

void do_work(int &counter,int nr_of_tickets, double a, double b, int num_trapezoids, double &result){
    int ticket;
    while((ticket=atomic_counter(counter,nr_of_tickets)) >= 0){
        //use number tag to get a data chunk, local_a and local_b
        int trapezoids_per_block = num_trapezoids / nr_of_tickets;
        double interval_length = (b - a) / (double)nr_of_tickets;
        double local_a = a + ticket * interval_length;
        double local_b = local_a + interval_length;
        int local_trapezoids = (ticket == nr_of_tickets-1) ? num_trapezoids - (trapezoids_per_block * (nr_of_tickets - 1)) : trapezoids_per_block; //check -1 
        integrate(local_a,local_b,local_trapezoids, std::ref(result));
        
    }
}


void print_help() {
    std::cout << "Usage: integrate [options]\n"
              << "Options:\n"
              << "  <num_trapezoids>    Number of trapezoids (required)\n"
              << "  <num_threads>       Number of threads (required)\n"
              << "  <bucket_scaling>    Scaling factor for work bucket size (default = 10000)"
              << "  -h                  Show this help message\n";
}

int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 4) {
        std::cerr << "Error: Incorrect number of arguments.\n";
        print_help();
        return 1;
    }
    
    if (std::string(argv[1]) == "-h" || std::string(argv[2]) == "-h" || std::string(argv[3]) == "-h") {
        print_help();
        return 0;
    }
    
    int num_trapezoids;
    int num_threads;
    int bucket_scaling = 10000;

    try
    {
        num_trapezoids = std::stoi(argv[1]);
        num_threads = std::stoi(argv[2]);
        if (argc == 4){
            bucket_scaling = std::stoi(argv[3]);
        }
    }
    catch (std::exception const&)
    {
        std::cout << "Invalid argument(s)";
        print_help();
        exit(1);
    }
    

    if (num_threads <= 0 || num_trapezoids <= 0 || bucket_scaling <= 0) {
        std::cerr << "Error: Threads, trapezoids and bucket scaling must be positive.\n";
        return 1;
    }
    if (num_threads > 64){
        std::cerr << "Error: Yoo bro don't go crazy on the number of threads ok?!.\n";
        return 1;
    }
    

    double a = 0.0; 
    double b = 1.0;  
    double result = 0.0;

    std::thread *t = new std::thread[num_threads];

    int nr_of_tickets = (num_trapezoids > 64*bucket_scaling) ? (num_trapezoids/bucket_scaling) * num_threads : num_trapezoids;
    int counter = 0;
    
    auto start_time = std::chrono::high_resolution_clock::now();
    

    for (int i = 0; i < num_threads; ++i) {
        t[i] = std::thread(do_work, std::ref(counter), nr_of_tickets, a, b, num_trapezoids, std::ref(result));
    }

    for (int i=0; i<num_threads; ++i)
    {
        t[i].join();
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end_time - start_time;

    //std::cout << "Estimated integral: " << result << std::endl;
    std::cout << elapsed.count() << std::endl;

    return 0;
}
