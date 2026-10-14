#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <utime.h>

int main(int argc, char *argv[]) {
    struct stat buf;
    struct utimbuf time_buf;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source_file> <target_file>\n", argv[0]);
        exit(1);
    }

    if (stat(argv[1], &buf) < 0) {
        perror("stat()");
        exit(1);
    }

    time_buf.actime = buf.st_atime;
    time_buf.modtime = buf.st_mtime;

    if (utime(argv[2], &time_buf) < 0) {
        perror("utime()");
        exit(1);
    }

    return 0;
}
