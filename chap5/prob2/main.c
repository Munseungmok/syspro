#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFSIZE 512

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);

    if (fd == -1) {
        perror("File open error");
        return 1;
    }

    char buf[BUFSIZE];
    ssize_t nread;
    long total = 0;

    while ((nread = read(fd, buf, BUFSIZE)) > 0) {
        total += nread;
    }

    printf("%s File size : %ld Byte\n", argv[1], total);

    close(fd);

    return 0;
}
