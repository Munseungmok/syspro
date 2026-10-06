#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    int fd = open(argv[1], O_RDWR);

    if (fd == -1) {
        printf("File open error\n");
        return 1;
    } else {
        printf("file  %s success : %d\n", argv[1], fd);
    }

    close(fd);

    return 0;
}
