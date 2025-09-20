#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void func1(void) {
    printf("Cleanup function 1 called\n");
}


void func2(void) {
    printf("Cleanup function 2 called\n");
}



int main(){
    if (atexit(func1) != 0) {
        fprintf(stderr, "Failed to register cleanup1\n");
        return 1;
    }
    if (atexit(func2) != 0) {
        fprintf(stderr, "Failed to register cleanup2\n");
        return 1;
    }

    printf("Main function is running\n");

    // For experimenting
    // exit(0);

    printf("Main function is ending normally\n");
    return 0; //Same as exit(0)
}