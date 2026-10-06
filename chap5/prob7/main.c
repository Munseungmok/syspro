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

    int fd = open(argv[1], O_RDWR);
    if (fd == -1) {
        perror(argv[1]);
        return 1;
    }

    char c;
    struct student rec;

    do {
        printf("Enter StudentID to be modified: ");
        if (scanf("%d", &rec.id) != 1) {
            printf("Input error\n");
            while (getchar() != '\n');
            continue;
        }

        lseek(fd, (long)(rec.id - START_ID) * sizeof(rec), SEEK_SET);

        if ((read(fd, &rec, sizeof(rec)) > 0) && (rec.id != 0)) {
            printf("StuID:%-9d Name:%-12s Score: %d\n", rec.id, rec.name, rec.score);
            printf("New Score: ");
            scanf("%d", &rec.score);

            lseek(fd, (long)-(long)sizeof(rec), SEEK_CUR);
            write(fd, &rec, sizeof(rec));
        } else {
            printf("Record %d Null\n", rec.id);
        }

        printf("Continue?(Y/N)");
        scanf(" %c", &c);

    } while (c == 'Y' || c == 'y');

    close(fd);

    return 0;
}
