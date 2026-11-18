#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#define MAXLINE 1024
#define MAXARG 64

void execute_cmd(char *cmd) {
    char *args[MAXARG];
    char *infile = NULL;
    char *outfile = NULL;
    int bg = 0;
    int i = 0;

    int len = strlen(cmd);
    while (len > 0 && (cmd[len - 1] == ' ' || cmd[len - 1] == '\t' || cmd[len - 1] == '\n')) {
        cmd[--len] = '\0';
    }
    if (len == 0) return;

    if (cmd[len - 1] == '&') {
        bg = 1;
        cmd[--len] = '\0';
    }

    char *token = strtok(cmd, " \t\n");
    while (token != NULL && i < MAXARG - 1) {
        if (strcmp(token, ">") == 0) {
            token = strtok(NULL, " \t\n");
            if (token != NULL) outfile = token;
        } else if (strcmp(token, "<") == 0) {
            token = strtok(NULL, " \t\n");
            if (token != NULL) infile = token;
        } else {
            args[i++] = token;
        }
        token = strtok(NULL, " \t\n");
    }
    args[i] = NULL;

    if (args[0] == NULL) return;
    if (strcmp(args[0], "exit") == 0) exit(0);

    int pid = fork();
    if (pid == 0) {
        if (infile != NULL) {
            int fd_in = open(infile, O_RDONLY);
            if (fd_in < 0) {
                perror("open infile");
                exit(1);
            }
            dup2(fd_in, STDIN_FILENO);
            close(fd_in);
        }
        if (outfile != NULL) {
            int fd_out = open(outfile, O_CREAT | O_TRUNC | O_WRONLY, 0660);
            if (fd_out < 0) {
                perror("open outfile");
                exit(1);
            }
            dup2(fd_out, STDOUT_FILENO);
            close(fd_out);
        }
        execvp(args[0], args);
        perror("execvp");
        exit(1);
    } else if (pid > 0) {
        if (!bg) {
            waitpid(pid, NULL, 0);
        } else {
            printf("[Background PID: %d]\n", pid);
        }
    } else {
        perror("fork");
    }
}

int main() {
    char line[MAXLINE];
    char *cmds[MAXARG];

    while (1) {
        printf("[shell] ");
        fflush(stdout);

        if (fgets(line, MAXLINE, stdin) == NULL) break;

        int num_cmds = 0;
        char *cmd = strtok(line, ";");
        while (cmd != NULL && num_cmds < MAXARG - 1) {
            cmds[num_cmds++] = cmd;
            cmd = strtok(NULL, ";");
        }

        for (int i = 0; i < num_cmds; i++) {
            execute_cmd(cmds[i]);
        }
    }

    return 0;
}
