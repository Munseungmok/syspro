#include <stdio.h>
#include "student.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("사용법: %s [file_name.txt]\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "w");
    if (fp == NULL) {
        printf("파일 열기 오류\n");
        return 1;
    }

    student s;
    printf("학번  이름  점수\n");
    while (scanf("%d %19s %hd", &s.id, s.name, &s.score) == 3) {
        fprintf(fp, "%d %s %hd\n", s.id, s.name, s.score);
    }

    fclose(fp);
    return 0;
}
