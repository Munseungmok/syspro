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
    if ((fd = open(argv[1], O_RDWR)) == -1) {
        perror(argv[1]);
        exit(2);
    }

    printf("\nEnter StudentID you want to modify : ");
    while (scanf("%d", &id) == 1) {
        lock.l_type = F_WRLCK;             /* 쓰기 잠금 */
        lock.l_whence = SEEK_SET;
        lock.l_start = (id - START_ID) * sizeof(record);
        lock.l_len = sizeof(record);
        if (fcntl(fd, F_SETLKW, &lock) == -1) {
            perror(argv[1]);
            exit(3);
        }

        lseek(fd, (long)(id - START_ID) * sizeof(record), SEEK_SET);
        if (read(fd, &record, sizeof(record)) > 0 && record.id != 0) {
            printf("Name:%s\t StuID:%d\t Score:%d\n", record.name, record.id, record.score);
            printf("Enter new score : ");
            scanf("%d", &record.score);    /* 잠금을 건 상태에서 점수 입력 */
            lseek(fd, (long)(id - START_ID) * sizeof(record), SEEK_SET);
            write(fd, &record, sizeof(record));
        } else {
            printf("No record %d \n", id);
        }

        lock.l_type = F_UNLCK;             /* 찾지 못한 경우에도 잠금 해제 */
        fcntl(fd, F_SETLK, &lock);

        printf("\nEnter StudentID you want to modify : ");
    }
    close(fd);
    return 0;
}
