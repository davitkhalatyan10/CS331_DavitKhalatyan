#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* thread_creator(void* arg) {
    int thread_num = *(int*)arg;
    pthread_t tid = pthread_self();

    printf("Thread %d is running. (Thread ID: %lu)\n", thread_num, tid);

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[3];
    int thread_args[3];

    for (int i = 0; i < 3; i++) {
        thread_args[i] = i + 1;
        int result = pthread_create(&threads[i], NULL, thread_creator, &thread_args[i]);
        if (result != 0) {
            perror("pthread_create failed");
            exit(EXIT_FAILURE);
        }
    }


    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Main thread: All threads have completed.\n");
    return 0;
}
