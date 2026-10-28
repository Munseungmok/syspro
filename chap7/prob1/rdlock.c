#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include "student.h"

int main(int argc, char *argv[]) {
    int fd, id;
    struct student record;
    struct flock lock;

    if (argc < 2) {                        /* 예외처리: 인자 부족 */
        fprintf(stderr, "How to use : %s file\n", argv[0]);
        exit(1);
    }
    if ((fd = open(argv[1], O_RDONLY)) == -1) {
        perror(argv[1]);
        exit(2);
    }

    printf("\nEnter StudentID to search : ");
    while (scanf("%d", &id) == 1) {
        lock.l_type = F_RDLCK;             /* 읽기 잠금 */
        lock.l_whence = SEEK_SET;
        lock.l_start = (id - START_ID) * sizeof(record);
        lock.l_len = sizeof(record);
        if (fcntl(fd, F_SETLKW, &lock) == -1) {   /* 잠금 실패 시 경로 출력 후 종료 */
            perror(argv[1]);
            exit(3);
        }

        lseek(fd, (long)(id - START_ID) * sizeof(record), SEEK_SET);
        if (read(fd, &record, sizeof(record)) > 0 && record.id != 0)
            printf("Name:%s\t StuID:%d\t Score:%d\n", record.name, record.id, record.score);
        else
            printf("No record %d \n", id);

        lock.l_type = F_UNLCK;             /* 잠금 해제 */
        fcntl(fd, F_SETLK, &lock);

        printf("\nEnter StudentID to search : ");
    }
    close(fd);
    return 0;
}
