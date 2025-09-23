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
        int status;
        pid_t temp = waitpid(pid, &status, 0);
        pid_t pid2 = fork();
        if (pid2 == 0){
            printf("Second Child Process: ");
        }
        else{
            int status2;
            pid_t temp2 = waitpid(pid2, &status2, 0);
            printf("Exit Status of First Child: %d\n", status);
            printf("Exit Status of Second Child: %d\n", status2);
            printf("Parent Process: ");
        }
    }
