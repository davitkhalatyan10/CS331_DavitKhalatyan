#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>

#define MAX_LINE 512

int main() {
    int fd;
    char input[MAX_LINE];
    ssize_t bytes_read;
    pid_t pid = getpid();


    fd = open("log.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd < 0) {
        perror("Error opening log.txt");
        exit(EXIT_FAILURE);
    }

    printf("Type a log message: ");
    fflush(stdout);


    bytes_read = read(STDIN_FILENO, input, MAX_LINE - 1);
    if (bytes_read < 0) {
        perror("Error reading input");
        close(fd);
        exit(EXIT_FAILURE);
    }
    input[bytes_read] = '\0';  // Null-terminate


    if (input[bytes_read - 1] == '\n') {
        input[bytes_read - 1] = '\0';
    }


    char message[MAX_LINE + 64];
    snprintf(message, sizeof(message), "PID=%d: %s\n", pid, input);


    if (write(fd, message, strlen(message)) < 0) {
        perror("Error writing to log.txt");
        close(fd);
        exit(EXIT_FAILURE);
    }


    off_t pos = lseek(fd, 0, SEEK_CUR);
    if (pos == -1) {
        perror("Error getting file offset");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("Appended successfully. Current file offset: %ld\n", (long)pos);

    // Even though O_APPEND mode causes each write to append at the end of the file,
    // the file offset maintained by the process still grows as bytes are written.
    // lseek(fd, 0, SEEK_CUR) reflects this logical position (as if the file pointer
    // had advanced normally), even though the kernel moves the write position to EOF
    // automatically for each write.

    close(fd);
    return 0;
}
