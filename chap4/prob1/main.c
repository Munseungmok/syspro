#include <stdio.h>

int main(int argc, char *argv[]) {
    FILE *fp = stdin;

    if (argc > 1) {
        fp = fopen(argv[1], "r");
        if (fp == NULL) {
            printf("file open wrong\n");
            return 1;
        }
    }

    int ch;
    while ((ch = fgetc(fp)) != EOF) {
        putchar(ch);
    }

    if (fp != stdin) {
        fclose(fp);
    }
    return 0;
}
