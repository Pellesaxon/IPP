#include <iostream>
#include <omp.h>
#include <vector>
#include <cassert>

static long num_steps = 100000000;
double step;
static int nr_of_threads = 4;
int main ()
{
    double pi = 0.0;
    double start_time, run_time;

    step = 1.0/(double) num_steps;
    start_time = omp_get_wtime();

    #pragma omp parallel num_threads(nr_of_threads)
    {
        int actual_nr_of_threads = omp_get_num_threads();
        assert(actual_nr_of_threads <= nr_of_threads);
        int thread_id = omp_get_thread_num();
        int interval_size = (int) num_steps/actual_nr_of_threads;
        int start = thread_id * interval_size;    
        int end = (thread_id != (actual_nr_of_threads-1)) ? start + interval_size : num_steps;
        double x, sum = 0.0;
        
        for (int i = start; i < end; i++){
            x = (i+0.5)*step;
            sum = sum + 4.0/(1.0+x*x);
        }
    #pragma omp critical
        pi = pi+sum;
    }
    
    pi = pi * step;
    run_time = omp_get_wtime() - start_time;
    printf("\n pi with %ld steps is %lf in %lf seconds\n ",num_steps,pi,run_time);
}	