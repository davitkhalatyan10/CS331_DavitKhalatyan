#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUF_SIZE 1024

int main() {
    char file1[256], file2[256];
    int fd1, fd2;
    ssize_t r1, r2;
    unsigned char buf1[BUF_SIZE], buf2[BUF_SIZE];
    off_t byte_index = 0;
    int difference_found = 0;


    printf("Enter first file path: ");
    scanf("%255s", file1);
    printf("Enter second file path: ");
    scanf("%255s", file2);


    fd1 = open(file1, O_RDONLY);
    if (fd1 < 0) {
        perror("Error opening first file");
        exit(EXIT_FAILURE);
    }

    fd2 = open(file2, O_RDONLY);
    if (fd2 < 0) {
        perror("Error opening second file");
        close(fd1);
        exit(EXIT_FAILURE);
    }


    while (1) {
        r1 = read(fd1, buf1, BUF_SIZE);
        r2 = read(fd2, buf2, BUF_SIZE);

        if (r1 < 0 || r2 < 0) {
            perror("Error reading files");
            close(fd1);
            close(fd2);
            exit(EXIT_FAILURE);
        }


        ssize_t min_read = (r1 < r2) ? r1 : r2;
        for (ssize_t i = 0; i < min_read; i++) {
            if (buf1[i] != buf2[i]) {
                printf("Files differ at byte %ld\n", byte_index + i);
                difference_found = 1;
                break;
            }
        }

        if (difference_found)
            break;


        if (r1 == 0 || r2 == 0)
            break;

        byte_index += min_read;
    }


    if (!difference_found) {
        if (r1 == 0 && r2 == 0) {
            printf("Files are identical\n");
        } else if (r1 < r2) {
            printf("Files differ at byte %ld (first file ended)\n", byte_index);
            difference_found = 1;
        } else if (r2 < r1) {
            printf("Files differ at byte %ld (second file ended)\n", byte_index);
            difference_found = 1;
        }
    }

    close(fd1);
    close(fd2);

    return difference_found ? EXIT_FAILURE : EXIT_SUCCESS;
}
