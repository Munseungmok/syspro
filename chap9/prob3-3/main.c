#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    pid_t pid;
    int status, child;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command> [<args>...]\n", argv[0]);
        return 1;
    }

    pid = fork();
    if (pid == 0) {
        execvp(argv[1], &argv[1]);
        perror("execvp");
        exit(1);
    } else if (pid > 0) {
        child = wait(&status);
        printf("[%d] child process %d end\n", (int)getpid(), (int)child);
        printf("end code %d\n", status >> 8);
    } else {
        perror("fork");
    }
    return 0;
}
