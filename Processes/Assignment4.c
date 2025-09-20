#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
    pid_t pid = fork();
    if (pid == 0){
        printf("Child Process: %d\n", (int) getpid());
        exit(1);
    }
    else{
        int exitcd;
        pid_t status = waitpid(pid, &exitcd, 0);
        pid_t pid2 = fork();
        if (pid2 == 0){
            printf("Second Child Process: %d\n", (int) getpid());
            exit(5);
        }
        else{
            int temp;
            pid_t status2 = waitpid(pid2, &temp, 0);
            if(WIFEXITED(exitcd)){
                printf("Normally Exited Status of First Child: %d\n", WEXITSTATUS(exitcd));
            }
            else{
                printf("First Child Exited With Error");
            }
            if(WIFEXITED(temp)){
                printf("Normally Exited Status of Second Child: %d\n", WEXITSTATUS(temp));
            }
            else{
                printf("Second Child Exited With Error");
            }
            printf("Parent Process: %d\n", (int) getpid());
        }
    }
}

