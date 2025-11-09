#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {
    const char *filename = "data.txt";
    const char *text = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int fd;
    ssize_t bytes_written;
    char buffer[64];
    off_t size_before, size_after;


    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }

    bytes_written = write(fd, text, strlen(text));
    if (bytes_written < 0) {
        perror("Error writing to file");
        close(fd);
        exit(EXIT_FAILURE);
    }

    close(fd);
    printf("Wrote %zd bytes to %s\n", bytes_written, filename);


    fd = open(filename, O_RDWR);
    if (fd < 0) {
        perror("Error reopening file");
        exit(EXIT_FAILURE);
    }


    size_before = lseek(fd, 0, SEEK_END);
    if (size_before == -1) {
        perror("Error getting file size (before truncation)");
        close(fd);
        exit(EXIT_FAILURE);
    }
    printf("File size before truncation: %ld bytes\n", (long) size_before);


    if (ftruncate(fd, 10) < 0) {
        perror("Error truncating file");
        close(fd);
        exit(EXIT_FAILURE);
    }


    size_after = lseek(fd, 0, SEEK_END);
    if (size_after == -1) {
        perror("Error getting file size (after truncation)");
        close(fd);
        exit(EXIT_FAILURE);
    }
    printf("File size after truncation: %ld bytes\n", (long) size_after);


    if (lseek(fd, 0, SEEK_SET) == -1) {
        perror("Error rewinding file");
        close(fd);
        exit(EXIT_FAILURE);
    }

    ssize_t bytes_read = read(fd, buffer, sizeof(buffer) - 1);
    if (bytes_read < 0) {
        perror("Error reading file");
        close(fd);
        exit(EXIT_FAILURE);
    }

    buffer[bytes_read] = '\0';
    printf("Remaining content: \"%s\"\n", buffer);

    close(fd);
    return 0;
}
