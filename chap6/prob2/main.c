#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    long mode;
    mode_t perm;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <mode> <file>\n", argv[0]);
        exit(1);
    }

    mode = strtol(argv[1], NULL, 8);
    perm = (mode_t)mode;

    if (chmod(argv[2], perm) < 0) {
        perror("chmod()");
        exit(1);
    }

    return 0;
}
