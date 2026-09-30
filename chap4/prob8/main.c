#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("사용법: %s [stdin|stdout|stderr|file_name]\n", argv[0]);
        return 1;
    }

    FILE *fp = NULL;
    char *target = argv[1];

    if (strcmp(target, "stdin") == 0) fp = stdin;
    else if (strcmp(target, "stdout") == 0) fp = stdout;
    else if (strcmp(target, "stderr") == 0) fp = stderr;
    else {
        fp = fopen(target, "r");
        if (fp == NULL) {
            printf("파일 열기 오류\n");
            return 1;
        }
    }

    if (fp == stdin) {
        printf("한 글자 입력: ");
        fgetc(stdin);
    } else if (fp == stdout) {
        fputs("", stdout);
    } else if (fp != stderr) {
        fgetc(fp);
    }

    int buf_size = fp->_IO_buf_end - fp->_IO_buf_base;

    if (fp->_flags & 0x0002) {
        printf("스트림 = %s, 버퍼 미사용, 버퍼 크기=0\n", target);
    } else if (fp->_flags & 0x0200) {
        printf("스트림 = %s, 줄 버퍼 사용, 버퍼 크기=%d\n", target, buf_size);
    } else {
        printf("스트림 = %s, 완전 버퍼 사용, 버퍼 크기=%d\n", target, buf_size);
    }

    if (fp != stdin && fp != stdout && fp != stderr) {
        fclose(fp);
    }
    return 0;
}


