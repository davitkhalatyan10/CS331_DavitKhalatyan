#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
    pid_t pid = fork();

    if (pid == 0){
        int ret = execl("/bin/echo", "echo", "Hello from child.", (char *)NULL);
    }
    else{
        wait(NULL);
        printf("Parent process done\n");
    }

    return 0;
}