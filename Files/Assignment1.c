#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main() {
    char src[256], dest[256];
    int src_fd, dest_fd;
    ssize_t bytes_read, bytes_written, total_bytes = 0;
    char buffer[BUFFER_SIZE];


    printf("Enter source file path: ");
    scanf("%255s", src);

    printf("Enter destination file path: ");
    scanf("%255s", dest);


    src_fd = open(src, O_RDONLY);
    if (src_fd < 0) {
        perror("Error opening source file");
        exit(EXIT_FAILURE);
    }


    dest_fd = open(dest, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd < 0) {
        perror("Error opening/creating destination file");
        close(src_fd);
        exit(EXIT_FAILURE);
    }


    while ((bytes_read = read(src_fd, buffer, BUFFER_SIZE)) > 0) {
        bytes_written = write(dest_fd, buffer, bytes_read);
        if (bytes_written < 0) {
            perror("Error writing to destination file");
            close(src_fd);
            close(dest_fd);
            exit(EXIT_FAILURE);
        }
        total_bytes += bytes_written;
    }

    if (bytes_read < 0) {
        perror("Error reading source file");
    } else {
        printf("Copied %zd bytes successfully.\n", total_bytes);
    }

    close(src_fd);
    close(dest_fd);
    return 0;
}
