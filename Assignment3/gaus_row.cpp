#include <iostream>
#include <vector>
#include <thread>
#include <functional>
#include <mutex>
#include <cmath>
#include <string>
#include <chrono>
#include <omp.h>

int main(int argc, char *argv[]) {
    int num_threads;
    int matrix_size;
    if (argc != 3) {
		fprintf(stderr, "Usage: ./exec Matrix-size Threads\n");
		exit(-1);
	}
    else {
        matrix_size= std::stoi(argv[1]);
        num_threads= std::stoi(argv[2]);
	}
    if (num_threads > 64){
        std::cerr << "Error: Yoo bro don't go crazy on the number of threads ok?!.\n";
        return 1;
    }



    
    std::vector<std::vector<double>> A(matrix_size,std::vector<double>(matrix_size,5));
    for (int row = 0; row < matrix_size; row++){
        for (int col = 0; col < matrix_size; col++){
            if (col<row){
                A[row][col] = 0;
            }
            else {
                A[row][col] = row + col;
            }
        }
    }
    
    std::vector<double> b(matrix_size,3);
    std::vector<double> x(matrix_size,0);

    omp_set_dynamic(0);
    omp_set_num_threads(num_threads);
    int val = 0;
    int sum = 0;

    auto start_time = std::chrono::high_resolution_clock::now();

    for (int row = matrix_size-1; row >= 0; row--) {
        x[row] = b[row];

        #pragma omp parallel for shared(A, b, x) private(val) reduction(-:sum) schedule(static)
        for (int col = row+1; col < matrix_size; col++) {
            val = A[row][col] * x[col];
            sum -= val;
        }
        x[row] = sum / A[row][row];
    }

    // for (int i = 0; i<matrix_size; i++)
    //     std::cout << x[i] << " ";
    // std::cout << "\n";

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end_time - start_time;
    std::cout << elapsed.count() << std::endl;


       return 0;
}