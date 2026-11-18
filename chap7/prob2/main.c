#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "student.h"

/* lockf()를 이용한 학생 데이터베이스 수정 프로그램 */
int main(int argc, char *argv[]) {
    int fd, id;
    off_t pos;
    struct student record;

    if (argc < 2) {                          /* 예외처리: 인자 부족 */
        fprintf(stderr, "How to use : %s file\n", argv[0]);
        exit(1);
    }
    if ((fd = open(argv[1], O_RDWR)) == -1) {
        perror(argv[1]);
        exit(2);
    }

    printf("\nEnter StudentID you want to modify : ");
    while (scanf("%d", &id) == 1) {
        if (id < START_ID) {                 /* 학번이 범위 밖이면 위치를 계산할 수 없음 */
            printf("No record %d \n", id);
            printf("\nEnter StudentID you want to modify : ");
            continue;
        }
        pos = (off_t)(id - START_ID) * sizeof(record);

        /* lockf()는 현재 파일 위치부터 잠금을 걸기 때문에 먼저 lseek 해야 함 */
        lseek(fd, pos, SEEK_SET);
        if (lockf(fd, F_LOCK, sizeof(record)) == -1) {   /* 쓰기 잠금 (잠금 중이면 대기) */
            perror(argv[1]);
            exit(3);
        }

        lseek(fd, pos, SEEK_SET);
        if (read(fd, &record, sizeof(record)) > 0 && record.id != 0) {
            printf("Name:%s\t StuID:%d\t Score:%d\n", record.name, record.id, record.score);
            printf("Enter new score : ");
            scanf("%d", &record.score);
            lseek(fd, pos, SEEK_SET);
            write(fd, &record, sizeof(record));
        } else {
            printf("No record %d \n", id);
        }

        lseek(fd, pos, SEEK_SET);
        lockf(fd, F_ULOCK, sizeof(record));  /* 잠금 해제 */

        printf("\nEnter StudentID you want to modify : ");
    }

    close(fd);
    exit(0);
}

