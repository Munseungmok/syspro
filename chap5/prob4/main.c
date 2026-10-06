#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(void) {
    int fd1 = creat("myfile", 0600);
    if (fd1 == -1) {
        perror("File creation error");
        return 1;
    }

    char *msg1 = "Hello! Linux";
    if (write(fd1, msg1, strlen(msg1)) == -1) {
        perror("Write error 1");
        close(fd1);
        return 1;
    }

    int fd2 = dup(fd1);
    if (fd2 == -1) {
        perror("Dup error");
        close(fd1);
        return 1;
    }

    char *msg2 = "Bye! Linux";
    if (write(fd2, msg2, strlen(msg2)) == -1) {
        perror("Write error 2");
        close(fd1);
        close(fd2);
        return 1;
    }

    close(fd1);
    close(fd2);

    return 0;
}
