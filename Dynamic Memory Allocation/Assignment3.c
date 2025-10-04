#include <stdio.h>
#include <stdlib.h>

int main(){
    int *arr;

    arr = (int *) malloc(10 * sizeof(int));

    printf("Enter 10 integers: ");
    for(int i = 0; i < 10; i++){
        scanf("%d", &arr[i]);
    }

    arr = (int *) realloc(arr, 5 * sizeof(int));

    printf("Array after resizing: ");
    for(int i = 0; i < 5; i++){
        printf("%d", arr[i]);
    }
    printf("\n");

    free(arr);
    return 0;
}