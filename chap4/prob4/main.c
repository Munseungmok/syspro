#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("How to use:%s [file_name.txt]\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "w");
    if (fp == NULL) {
        printf("File Wrong\n");
        return 1;
    }

    int id;
    char name[20];
    short score;

    printf("StudentID Name Score\n");
    while (scanf("%d %19s %hd", &id, name, &score) == 3) {
        fprintf(fp, "%d %s %hd\n", id, name, score);
    }

    fclose(fp);
    return 0;
}
