
// gcc pth2.c -o pth2 -lpthread -lm

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <sys/time.h>

int *arr;
int *arr2;
int arr_len = 500000000;
int nthreads = 4;

#define DO_COMPLEX_CALCULATIONS(x) (int)tan((double)(x)) + \
                                   (int)sin((double)(x)) + \
                                   (int)cos((double)(x)) + \
                                   (int)tanh((double)(x)) + \
                                   (int)sinh((double)(x)) + \
                                   (int)cosh((double)(x)) + \
                                   (int)atan((double)(x)) + \
                                   (int)asin((double)(x)) + \
                                   (int)acos((double)(x)) + \
                                   (int)atanh((double)(x)) + \
                                   (int)asinh((double)(x)) + \
                                   (int)acosh((double)(x)) + \
                                   (int)exp((double)(x)) + \
                                   (int)log((double)(x)) + \
                                   (int)log10((double)(x)) + \
                                   (int)log2((double)(x)) + \
                                   (int)sqrt((double)(x))

void * add_to_arr(void * n) {
    int start = arr_len / nthreads * (int)n;
    int end = start + arr_len / nthreads;
    for (int i = start; i < end; i+=1) {
        arr2[i] = DO_COMPLEX_CALCULATIONS(arr[i]);
    }
}

int main (int argc, char ** argv) {
    arr = malloc(arr_len * sizeof(int));
    arr2 = malloc(arr_len * sizeof(int));

    struct timeval start, finish;

    gettimeofday(&start, NULL);

    for (int i = 0; i < arr_len; i++) {
        arr2[i] = DO_COMPLEX_CALCULATIONS(arr[i]);
    }

    gettimeofday(&finish, NULL);
    double elapsed = ((double)(finish.tv_usec - start.tv_usec) / 1000000.0) + finish.tv_sec - start.tv_sec;

    printf("time elapsed %lf seconds\n", (double)elapsed);

    pthread_t * my_threads = malloc(nthreads * sizeof(pthread_t));

    gettimeofday(&start, NULL);
		
	for (int i = 0; i < nthreads; i++) {
		pthread_create(&my_threads[i], NULL, add_to_arr, (void *)i);
	}
		
	for (int i = 0; i < nthreads; i++) {
		pthread_join(my_threads[i], NULL);
	}

    gettimeofday(&finish, NULL);
    elapsed = ((double)(finish.tv_usec - start.tv_usec) / 1000000.0) + finish.tv_sec - start.tv_sec;

    printf("time elapsed %lf seconds\n", (double)elapsed);

    return 0;
}
