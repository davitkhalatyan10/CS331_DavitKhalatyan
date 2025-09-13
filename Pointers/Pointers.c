#include <stdio.h>

void swap(int *a, int *b) {

    int temp = *a;
    *a = *b;
    *b = temp;
}

int main (void){

    // Task 1

    int x = 2;
    int *p = &x;
    printf("%p\n", &x);
    printf("%p\n", p);

    // Task 2

    int vars[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++) {
        int *p2 = &vars[i];
        printf("%p\n", p2);
    }

    int *p3 = &vars[0];
    for (int i = 0; i < 5; i++) {
        *p3 = *p3 + 1;
        printf("%d\n", *p3);
        p3++;
    }

    int *parr = vars;
    for (int i = 0; i < 5; i++) {
        printf("%d\n", *(parr + i));
        printf("%d\n", vars[i]);
    }

    //Task 3

    int a = 2;
    int b = 3;
    printf("Before: a = %d, b = %d\n", a, b);
    swap(&a, &b);
    printf("After: a = %d, b = %d\n", a, b);

    //Task 4

    int var = 1;
    int *ptr = &var;
    int **ptr2 = &ptr;
    printf("Using Pointer: %d\n", *ptr);
    printf("Using Double Pointer: %d\n", **ptr2);

    //Task 5

    char str[] = "Hello";
    char *pstr = str;
    for (int i = 0; i < 5; i++) {
        printf("%c", *(pstr + i));
        if (i == 4) {
            printf("\n");
        }
    }

    int count = 0;
    while (*pstr != '\0') {
        count++;
        pstr++;
    }
    printf("Number of Characters: %d\n", count);

    return 0;
}