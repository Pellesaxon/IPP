
// gcc pth3.c -o pth3 -g -lpthread -fsanitize=thread

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

int x = 0;
pthread_mutex_t mut;

void * increment(void * n) {
    pthread_mutex_lock(&mut);
    x++;
    pthread_mutex_unlock(&mut);
	return NULL;
}

void * decrement(void * n) {
    pthread_mutex_lock(&mut);
    x--;
    pthread_mutex_unlock(&mut);
	return NULL;
}

int main (int argc, char ** argv) {		
	pthread_t thread1, thread2;

    pthread_mutex_init(&mut, NULL);

    pthread_create(&thread1, NULL, increment, NULL);
    pthread_create(&thread2, NULL, decrement, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

	return 0;
}
