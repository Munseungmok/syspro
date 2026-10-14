#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    char buf[1024];
    int n;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <symlink>\n", argv[0]);
        exit(1);
    }

    if ((n = readlink(argv[1], buf, sizeof(buf) - 1)) < 0) {
        perror("readlink()");
        exit(1);
    }

    buf[n] = '\0';

    if (write(STDOUT_FILENO, buf, n) < 0) {
        perror("write()");
        exit(1);
    }
    write(STDOUT_FILENO, "\n", 1);

    return 0;
}
