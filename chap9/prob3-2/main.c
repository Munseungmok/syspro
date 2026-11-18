#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid1, pid2, pid3;
    printf("parental process start\n");

    if (fork() == 0) {
        execl("/bin/echo", "echo", "hello", NULL);
        exit(1);
    }
    if (fork() == 0) {
        execl("/bin/date", "date", NULL);
        exit(1);
    }
    if (fork() == 0) {
        execl("/bin/ls", "ls", "-l", NULL);
        exit(1);
    }

    for (int i = 0; i < 3; i++) {
        wait(NULL);
    }
    printf("parental process end\n");
    return 0;
}
