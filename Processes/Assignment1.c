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
                printf("Parent Process: ");
        }
        printf("%d\n", (int) getpid());
}