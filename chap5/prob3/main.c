#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFSIZE 512

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source_file> <target_file>\n", argv[0]);
        return 1;
    }

    int fd1 = open(argv[1], O_RDONLY);
    if (fd1 == -1) {
        perror("Source file open error");
        return 1;
    }

    int fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd2 == -1) {
        perror("Target file open error");
        close(fd1);
        return 1;
    }

    char buf[BUFSIZE];
    ssize_t nread;

    while ((nread = read(fd1, buf, BUFSIZE)) > 0) {
        if (write(fd2, buf, nread) != nread) {
            perror("Write error");
            close(fd1);
            close(fd2);
            return 1;
        }
    }

    close(fd1);
    close(fd2);

    return 0;
}
