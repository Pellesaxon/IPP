//First c++ program

#include <iostream>
#include <omp.h>

int main() {
    omp_set_num_threads(4);
    #pragma omp parallel
    {
        int ID = omp_get_thread_num();
        std::cout << "hello(" << ID <<") \n";
        std::cout << "world(" << ID <<") \n";
    }
    
}