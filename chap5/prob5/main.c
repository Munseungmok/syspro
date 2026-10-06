#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "student.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    int fd = open(argv[1], O_WRONLY | O_CREAT | O_EXCL, 0640);
    if (fd == -1) {
        perror(argv[1]);
        return 1;
    }

    printf("%-7s %-8s %-5s\n", "StuID", "Name", "Score");

    struct student rec;
    while (scanf("%d %s %d", &rec.id, rec.name, &rec.score) == 3) {
        lseek(fd, (long)(rec.id - START_ID) * sizeof(rec), SEEK_SET);
        write(fd, &rec, sizeof(rec));
    }

    close(fd);

    return 0;
}
