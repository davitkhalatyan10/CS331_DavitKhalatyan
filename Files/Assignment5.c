#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

int main() {
    int fd;
    ssize_t written;
    const char *start = "START";
    const char *end = "END";
    off_t offset;


    fd = open("sparse.bin", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("Error opening sparse.bin for writing");
        exit(EXIT_FAILURE);
    }


    written = write(fd, start, 5);
    if (written != 5) {
        perror("Error writing START");
        close(fd);
        exit(EXIT_FAILURE);
    }


    offset = lseek(fd, 1024 * 1024, SEEK_CUR);
    if (offset == (off_t)-1) {
        perror("Error seeking in file");
        close(fd);
        exit(EXIT_FAILURE);
    }


    written = write(fd, end, 3);
    if (written != 3) {
        perror("Error writing END");
        close(fd);
        exit(EXIT_FAILURE);
    }

    close(fd);


    fd = open("sparse.bin", O_RDONLY);
    if (fd < 0) {
        perror("Error reopening sparse.bin");
        exit(EXIT_FAILURE);
    }


    off_t filesize = lseek(fd, 0, SEEK_END);
    if (filesize == (off_t)-1) {
        perror("Error seeking to end");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("Apparent file size: %ld bytes\n", (long)filesize);
    close(fd);

    /*
    Explanation:
    This program creates a *sparse file* — a file with a logical size larger than
    the actual disk space used. When we call lseek() to jump forward 1 MiB without
    writing data, the kernel does not allocate physical blocks for that region.
    Instead, it records a “hole” in the file metadata.

    The apparent size (reported by 'ls -l' or lseek) includes the hole,
    but the actual disk usage (reported by 'du -h') is much smaller,
    because no physical storage is used for the skipped region.
    */
    return 0;
}
