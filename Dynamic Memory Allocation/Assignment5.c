#include <stdio.h>
#include <stdlib.h>

int main(){
    int n;
    int *grades;

    printf("Enter the number of students: ");
    scanf("%d", &n);

    grades = (int *) malloc(n * sizeof(int));

    printf("Enter the grades: ");
    for(int i = 0; i < n; i++){
        scanf("%d", &grades[i]);
    }

    int maxg = grades[0];
    int ming = grades[0];

    for(int i = 1; i < n; i++){
        if(maxg < grades[i]){
            maxg = grades[i];
        }
        else if(ming > grades[i]){
            ming = grades[i];
        }
    }

    printf("Highest grade: %d\n", maxg);
    printf("Lowest grade: %d\n", ming);

    free(grades);

    return 0;
}