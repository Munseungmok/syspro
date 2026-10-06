#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror(argv[1]);
        return 1;
    }

    printf("File read success\n");

    char savedText[100][100];
    int total_line = 0;
    int col = 0;
    char buf;

    while (read(fd, &buf, 1) > 0) {
        if (buf == '\n') {
            savedText[total_line][col] = '\0';
            total_line++;
            col = 0;
        } else {
            savedText[total_line][col++] = buf;
        }
    }
    if (col > 0) {
        savedText[total_line][col] = '\0';
        total_line++;
    }

    close(fd);

    printf("Total Line : %d\n", total_line);
    printf("You can choose 1 ~ %d Line\n", total_line);
    printf("Pls 'Enter' the line to select : ");

    char input[100];
    if (scanf("%s", input) != 1) return 1;

    if (strcmp(input, "*") == 0) {
        for (int i = 0; i < total_line; i++) {
            printf("%s\n", savedText[i]);
        }
    } else if (strchr(input, '-') != NULL) {
        int start, end;
        sscanf(input, "%d-%d", &start, &end);
        for (int i = start - 1; i < end && i < total_line; i++) {
            if (i >= 0) printf("%s\n", savedText[i]);
        }
    } else if (strchr(input, ',') != NULL) {
        char *token = strtok(input, ",");
        while (token != NULL) {
            int line = atoi(token);
            if (line >= 1 && line <= total_line) {
                printf("%s\n", savedText[line - 1]);
            }
            token = strtok(NULL, ",");
        }
    } else {
        int line = atoi(input);
        if (line >= 1 && line <= total_line) {
            printf("%s\n", savedText[line - 1]);
        }
    }

    return 0;
}
