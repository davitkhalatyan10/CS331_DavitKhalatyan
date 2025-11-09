#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    char path[256];
    int fd;
    off_t size;

    printf("Enter file path: ");
    scanf("%255s", path);


    fd = open(path, O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }


    size = lseek(fd, 0, SEEK_END);
    if (size == -1) {
        perror("Error determining file size");
        close(fd);
        exit(EXIT_FAILURE);
    }


    if (size == 0) {
        printf("\n");
        close(fd);
        return 0;
    }

    char ch;

    for (off_t pos = size - 1; pos >= 0; pos--) {
        if (lseek(fd, pos, SEEK_SET) == -1) {
            perror("Error seeking in file");
            close(fd);
            exit(EXIT_FAILURE);
        }

        if (read(fd, &ch, 1) != 1) {
            perror("Error reading file");
            close(fd);
            exit(EXIT_FAILURE);
        }


        write(STDOUT_FILENO, &ch, 1);
    }

    write(STDOUT_FILENO, "\n", 1);
    close(fd);
    return 0;
}
