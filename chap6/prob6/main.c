#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <original_file> <link_file>\n", argv[0]);
        exit(1);
    }

    if (link(argv[1], argv[2]) < 0) {
        perror("link()");
        exit(1);
    }

    return 0;
}
