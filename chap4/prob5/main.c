#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("사용법: %s [file_name.txt]\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("파일 열기 오류\n");
        return 1;
    }

    int id;
    char name[20];
    short score;

    printf("학번  이름  점수\n");
    while (fscanf(fp, "%d %19s %hd", &id, name, &score) == 3) {
        printf("%d %s %hd\n", id, name, score);
    }

    fclose(fp);
    return 0;
}
