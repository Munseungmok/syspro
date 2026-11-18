#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    pid_t pid;
    int fd, status, child;

    if (argc < 4) {
        fprintf(stderr, "Usage: %s <outfile> <cmd> <infile>\n", argv[0]);
        return 1;
    }

    pid = fork();
    if (pid == 0) {
        fd = open(argv[1], O_CREAT | O_TRUNC | O_WRONLY, 0660);
        if (fd < 0) {
            perror("open outfile");
            exit(1);
        }
        dup2(fd, STDOUT_FILENO);
        close(fd);

        int fd_in = open(argv[3], O_RDONLY);
        if (fd_in < 0) {
            perror("open infile");
            exit(1);
        }
        dup2(fd_in, STDIN_FILENO);
        close(fd_in);

        execlp(argv[2], argv[2], NULL);
        perror("execlp");
        exit(1);
    } else if (pid > 0) {
        child = wait(&status);
        printf("[%d] child process %d end\n", (int)getpid(), (int)child);
    } else {
        perror("fork");
    }
    return 0;
}
