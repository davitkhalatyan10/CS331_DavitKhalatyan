#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
    pid_t pid = fork();
    if (pid == 0){
        printf("Child Process: ");
    }
    else{
        pid_t status = wait(NULL);
        pid_t pid2 = fork();
        if (pid2 == 0){
            printf("Second Child Process: ");
        }
        else{
            int temp;
            pid_t status2 = waitpid(pid2, &temp, 0);
            printf("Exit Status of First Child: %d\n", status);
            printf("Exit Status of Second Child: %d\n", status2);
            printf("Parent Process: ");
        }
    }
    printf("%d\n", (int) getpid());
}