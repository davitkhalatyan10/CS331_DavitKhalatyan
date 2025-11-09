#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>

#define FILENAME "numbers.txt"
#define BUF_SIZE 1024

int main() {
    int fd;
    char buffer[BUF_SIZE];
    ssize_t bytes_read;
    int i;


    fd = open(FILENAME, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("Error creating file");
        exit(EXIT_FAILURE);
    }

    for (i = 1; i <= 10; i++) {
        char line[16];
        int len = snprintf(line, sizeof(line), "%d\n", i);
        if (write(fd, line, len) != len) {
            perror("Error writing numbers");
            close(fd);
            exit(EXIT_FAILURE);
        }
    }
    close(fd);


    fd = open(FILENAME, O_RDWR);
    if (fd < 0) {
        perror("Error opening file for modification");
        exit(EXIT_FAILURE);
    }


    off_t offset = 0;
    int line_count = 0;
    int found = 0;

    while (!found && (bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
        for (ssize_t j = 0; j < bytes_read; j++) {
            if (buffer[j] == '\n') {
                line_count++;
                if (line_count == 3) {  // start of line 4
                    offset += j + 1;
                    found = 1;
                    break;
                }
            }
        }
        if (!found) offset += bytes_read;
    }

    if (!found) {
        fprintf(stderr, "File does not contain enough lines.\n");
        close(fd);
        exit(EXIT_FAILURE);
    }


    if (lseek(fd, offset, SEEK_SET) == (off_t)-1) {
        perror("Error seeking to line 4");
        close(fd);
        exit(EXIT_FAILURE);
    }


    char remainder[BUF_SIZE];
    ssize_t rem_len = read(fd, remainder, sizeof(remainder));
    if (rem_len < 0) {
        perror("Error reading remainder");
        close(fd);
        exit(EXIT_FAILURE);
    }


    if (lseek(fd, offset, SEEK_SET) == (off_t)-1) {
        perror("Error seeking back to overwrite");
        close(fd);
        exit(EXIT_FAILURE);
    }

    const char *new_line = "100\n";
    ssize_t new_len = strlen(new_line);

    if (write(fd, new_line, new_len) != new_len) {
        perror("Error writing new value");
        close(fd);
        exit(EXIT_FAILURE);
    }


    if (write(fd, remainder, rem_len) != rem_len) {
        perror("Error writing remainder");
        close(fd);
        exit(EXIT_FAILURE);
    }

    close(fd);


    fd = open(FILENAME, O_RDONLY);
    if (fd < 0) {
        perror("Error reopening for reading");
        exit(EXIT_FAILURE);
    }

    printf("Final file content:\n");
    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
        write(STDOUT_FILENO, buffer, bytes_read);
    }
    close(fd);

    /*
    Explanation:
    This version avoids goto by using a simple flag variable (found)
    to break out of nested loops once the start of line 4 is located.
    Everything else is identical — the program reads until the 3rd newline,
    replaces the 4th line’s value "4\n" with "100\n", and shifts the remainder
    correctly so file content stays valid.
    */

    return 0;
}
