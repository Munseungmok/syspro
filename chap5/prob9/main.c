#include <stdio.h>
#include <stdlib.h>
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

    for (int i = total_line - 1; i >= 0; i--) {
        printf("%s\n", savedText[i]);
    }

    return 0;
}
