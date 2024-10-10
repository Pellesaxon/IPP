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
    int dim;
    int i,j,k;

    if (argc != 3) {
		fprintf(stderr, "Usage: ./exec Threads Dimentions\n");
		exit(-1);
	}
	else {
		num_threads = std::stoi(argv[1]); 
        dim = std::stoi(argv[2]);
	}
    
    if (num_threads < 1 || num_threads > 64 ) {
        fprintf(stderr, "Dont get out of hand with threads\n");
		exit(-1);
    }
    
    std::vector<std::vector<int>> a(dim,std::vector<int>(dim,5));
    std::vector<std::vector<int>> b(dim,std::vector<int>(dim,5));
    std::vector<std::vector<int>> c(dim,std::vector<int>(dim,5));

    
    /**
    
    
    
     */
    
    omp_set_dynamic(0);
    omp_set_num_threads(num_threads);

    

    auto start_time = std::chrono::high_resolution_clock::now();
    #pragma omp parallel default(none) private(i, j, k) shared (a, b, c, dim) 
    {
        #pragma omp for schedule(static) collapse(1)
        for (i = 0; i < dim; i++) {
            for (j = 0; j < dim; j++) {
                for (k = 0; k < dim; k++) {
                    if (!(k)){
                        c[i][j] = 0;
                    }
                    c[i][j] += a[i][k] * b[k][j];
                }
            }
        }
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end_time - start_time;
    std::cout << elapsed.count() << " for one paralized loop"<< std::endl;
    

    
    start_time = std::chrono::high_resolution_clock::now();
    #pragma omp parallel default(none) private(i, j, k) shared (a, b, c, dim)
    {
        #pragma omp for schedule(static) collapse(2) // 1, 2 or 3 depening on number of loops to paralleliz
        for (i = 0; i < dim; i++) {
            for (j = 0; j < dim; j++) {
                for (k = 0; k < dim; k++) {
                    if (!(k)){
                        c[i][j] = 0;
                    }
                    c[i][j] += a[i][k] * b[k][j];
                }
            }
        }
    }

    end_time = std::chrono::high_resolution_clock::now();
    elapsed = end_time - start_time;
    std::cout << elapsed.count() << " for two paralized loop" << std::endl;


    start_time = std::chrono::high_resolution_clock::now();
    #pragma omp parallel default(none) private(i, j, k) shared (a, b, c, dim)
    {
        #pragma omp for schedule(static) collapse(3) // 1, 2 or 3 depening on number of loops to paralleliz
        for (i = 0; i < dim; i++) {
            for (j = 0; j < dim; j++) {
                for (k = 0; k < dim; k++) {
                    if (!(k)){
                        c[i][j] = 0;
                    }
                    c[i][j] += a[i][k] * b[k][j];
                }
            }
        }
    }

    end_time = std::chrono::high_resolution_clock::now();
    elapsed = end_time - start_time;
    std::cout << elapsed.count() << " for three paralized loop" << std::endl;


    return 0;
}