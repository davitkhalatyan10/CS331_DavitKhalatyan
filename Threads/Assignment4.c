#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 5

int array[ARRAY_SIZE];

void* arr_square(void* arg) {
    int thread_number = (int)(long)arg;

    int a = array[thread_number];

    printf("Square of %d is %d\n", a, a*a);
    return NULL;
}

int main() {
    pthread_t threads[ARRAY_SIZE];
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = i + 1;
        if (pthread_create(&threads[i], NULL, arr_square, (void*)(long)i) != 0) {
            perror("Failed to create thread");
            return 1;
        }
    }

    for (int i = 0; i < ARRAY_SIZE; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Failed to join thread");
            return 1;
        }
    }

    return 0;
}