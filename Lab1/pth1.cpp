// g++ pth1.c -o pth1 -lpthread

// Make sure to run it many times and observe the outputs.
//
// Can you explain the results?


#include <iostream>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex;

void * say_hello(void * n) {
	std::cout << "Hello ";
    usleep(1);
    std::cout << "World ";
    usleep(1);
    std::cout << "from ";
    usleep(1);
    std::cout << "thread ";
    usleep(1);
    std::cout << (long) n << std::endl;
	return NULL;
}

void * say_hello_one_line(void *n) {
    usleep(10);
    std::cout << "Hello World from thread " << (long) n << std::endl;
    return NULL;
}

void * say_hello_mutex(void *n) {
    pthread_mutex_lock(&mutex);
	std::cout << "Hello ";
    usleep(1);
    std::cout << "World ";
    usleep(1);
    std::cout << "from ";
    usleep(1);
    std::cout << "thread ";
    usleep(1);
    std::cout << (long) n << std::endl;
	pthread_mutex_unlock(&mutex);
	return NULL;
}

int main (int argc, char ** argv) {
	long nthreads = 16;

	if (argc > 1)
		nthreads = atoi(argv[1]);

	pthread_t my_threads[nthreads];

	pthread_mutex_init(&mutex, NULL);

    std::cout << "----Saying Hello!----" << std::endl;

	for (long i = 0; i < nthreads; i++) {
		pthread_create(&my_threads[i], NULL, say_hello, (void *)i);
	}

	for (long i = 0; i < nthreads; i++) {
		pthread_join(my_threads[i], NULL);
	}

    std::cout << "----Saying Hello in one statement!----" << std::endl;

	for (long i = 0; i < nthreads; i++) {
		pthread_create(&my_threads[i], NULL, say_hello_one_line, (void *)i);
	}

	for (long i = 0; i < nthreads; i++) {
		pthread_join(my_threads[i], NULL);
	}

    std::cout << "----Saying Hello with a mutex lock!----" << std::endl;

	for (long i = 0; i < nthreads; i++) {
		pthread_create(&my_threads[i], NULL, say_hello_mutex, (void *)i);
	}

	for (long i = 0; i < nthreads; i++) {
		pthread_join(my_threads[i], NULL);
	}
	return 0;
}
