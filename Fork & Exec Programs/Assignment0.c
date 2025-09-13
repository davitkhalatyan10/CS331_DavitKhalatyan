#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main()
{
    printf("Before Fork\n");

    fork();
    printf("First Fork\n");
    sleep(10);

    fork();
    printf("Second Fork\n");
    sleep(10);

    fork();
    printf("Third Fork\n");
    sleep(10);

    return 0;
}