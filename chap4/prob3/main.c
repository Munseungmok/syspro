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

    char buffer[1024];
    int line_num = 1;

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%d %s", line_num++, buffer);
    }

    fclose(fp);
    return 0;
}
