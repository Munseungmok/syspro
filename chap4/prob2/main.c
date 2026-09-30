#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("사용법: %s file1.txt file2.txt\n", argv[0]);
        return 1;
    }

    FILE *src = fopen(argv[1], "r");
    if (src == NULL) {
        printf("파일 열기 오류\n");
        return 1;
    }

    FILE *dst = fopen(argv[2], "w");
    if (dst == NULL) {
        printf("파일 열기 오류\n");
        fclose(src);
        return 1;
    }

    int ch;
    while ((ch = fgetc(src)) != EOF) {
        fputc(ch, dst);
    }

    fclose(src);
    fclose(dst);
    return 0;
}
