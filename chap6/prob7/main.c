#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        exit(1);
    }

    if (unlink(argv[1]) < 0) {
        perror("unlink()");
        exit(1);
    }

    return 0;
}
