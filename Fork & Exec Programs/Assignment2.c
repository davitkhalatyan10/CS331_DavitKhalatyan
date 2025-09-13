#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
    pid_t pid = fork();

    if (pid == 0){
        int ret = execl("/usr/bin/ls", "ls", NULL);
    }
    else{
        wait(NULL);
        pid_t pid2 = fork();

        if (pid2 == 0){
            int ret2 = execl("/usr/bin/date", "date", NULL);
        }
        else{
            wait(NULL);
            printf("Parent process done\n");
        }
    }

    return 0;
}