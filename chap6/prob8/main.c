#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <target> <symlink>\n", argv[0]);
        exit(1);
    }

    if (symlink(argv[1], argv[2]) < 0) {
        perror("symlink()");
        exit(1);
    }

    return 0;
}
