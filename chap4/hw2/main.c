#include <stdio.h>
#include <string.h>

void print_file(FILE *fp, int show_line_num) {
    int ch;
    int line_num = 1;
    int is_start_of_line = 1;

    while ((ch = fgetc(fp)) != EOF) {
        if (show_line_num && is_start_of_line) {
            printf("%6d\t", line_num++);
            is_start_of_line = 0;
        }
        putchar(ch);
        if (ch == '\n') {
            is_start_of_line = 1;
        }
    }
}

int main(int argc, char *argv[]) {
    int show_line_num = 0;
    int start_idx = 1;

    // -n 옵션 확인
    if (argc > 1 && strcmp(argv[1], "-n") == 0) {
        show_line_num = 1;
        start_idx = 2;
    }

    // 파일 인수가 전달되지 않은 경우 (표준 입력 stdin 사용)
    if (start_idx == argc) {
        print_file(stdin, show_line_num);
        return 0;
    }

    // 파일 인수가 1개 이상 전달된 경우 (순차적 출력)
    for (int i = start_idx; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL) {
            printf("파일 열기 오류: %s\n", argv[i]);
            continue;
        }
        print_file(fp, show_line_num);
        fclose(fp);
    }

    return 0;
}
