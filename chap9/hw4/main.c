#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAXLINE 1024
#define MAXARG 64

int main() {
    char line[MAXLINE];
    char *args[MAXARG];
    int pid, child, status;

    while (1) {
        printf("Pls input cmd : ");
        fflush(stdout);

        if (fgets(line, MAXLINE, stdin) == NULL)
            break;

        int len = strlen(line);
        if (len > 0 && line[len - 1] == '\n')
            line[len - 1] = '\0';

        if (strlen(line) == 0)
            continue;

        if (strcmp(line, "exit") == 0) {
            printf("Exit\n");
            break;
        }

        int bg = 0;
        if (line[strlen(line) - 1] == '&') {
            bg = 1;
            line[strlen(line) - 1] = '\0';
            
            int l = strlen(line);
            while (l > 0 && (line[l - 1] == ' ' || line[l - 1] == '\t')) {
                line[--l] = '\0';
            }
        }

        int i = 0;
        char *token = strtok(line, " \t");
        while (token != NULL && i < MAXARG - 1) {
            args[i++] = token;
            token = strtok(NULL, " \t");
        }
        args[i] = NULL;

        if (args[0] == NULL)
            continue;

        pid = fork();
        if (pid == 0) {
            printf("[%d] child process start\n", getpid());
            execvp(args[0], args);
            perror("execvp fail");
            exit(1);
        } else if (pid > 0) {
            printf("[%d] Parent process start\n", pid);
            if (!bg) {
                child = wait(&status);
                printf("[%d] child process end %d\n", getpid(), child);
                printf("SUCCESS\n");
            } else {
                printf("[Background execution]\n");
            }
        } else {
            perror("fork fail");
        }
    }

    return 0;
}
