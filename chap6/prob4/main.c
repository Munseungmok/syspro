#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
    DIR *dp;
    struct dirent *dent;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
        exit(1);
    }

    if ((dp = opendir(argv[1])) == NULL) {
        perror("opendir()");
        exit(1);
    }

    while ((dent = readdir(dp)) != NULL) {
        printf("%s %lu\n", dent->d_name, dent->d_ino);
    }

    closedir(dp);

    return 0;
}
