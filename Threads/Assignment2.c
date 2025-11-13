#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 10

int array[ARRAY_SIZE];
long partial_sums[2];

void* sum_arr(void* arg) {
    int thread_number = (int)(long)arg;

    long sum = 0;
    for (int i = (thread_number - 1) * (ARRAY_SIZE / 2); i < thread_number * (ARRAY_SIZE / 2); i++) {
        sum += array[i];
    }
    printf("Thread %d partial sum: %ld \n", thread_number, sum);

    partial_sums[thread_number] = sum;
    return NULL;
}

int main() {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = i;
    }

    pthread_t thread1, thread2;

    if (pthread_create(&thread1, NULL, sum_arr, (void*)1) != 0) {
        perror("Failed to create thread 1");
        return 1;
    }

    if (pthread_create(&thread2, NULL, sum_arr, (void*)2) != 0) {
        perror("Failed to create thread 2");
        return 1;
    }

    if (pthread_join(thread1, NULL) != 0) {
        perror("Failed to join thread 1");
        return 1;
    }

    if (pthread_join(thread2, NULL) != 0) {
        perror("Failed to join thread 2");
        return 1;
    }

    return 0;
}