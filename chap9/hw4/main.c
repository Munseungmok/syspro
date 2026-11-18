#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXLINE 1024
#define MAXARG  64

int main(void)
{
    char line[MAXLINE];
    char *args[MAXARG];
    char *tok, *save;
    int argc, status, background;
    pid_t pid, child;

    while (1) {
        /* 1. 프롬프트를 내주고 명령어를 입력받는다 */
        printf("Pls input cmd : ");
        fflush(stdout);
        if (fgets(line, sizeof(line), stdin) == NULL)
            break;

        /* 2. strtok_r()로 명령줄 인수를 분리해서 args[]에 차례로 넣는다 */
        argc = 0;
        tok = strtok_r(line, " \t\n", &save);
        while (tok != NULL && argc < MAXARG - 1) {
            args[argc++] = tok;
            tok = strtok_r(NULL, " \t\n", &save);
        }
        args[argc] = NULL;
        if (argc == 0)                    /* 빈 줄이면 다시 입력받기 */
            continue;

        /* 마지막이 & 이면 후면 실행 표시 */
        background = 0;
        if (strcmp(args[argc - 1], "&") == 0) {
            background = 1;
            args[argc - 1] = NULL;
        }

        printf("[%d] Parent process start\n", getpid());
        fflush(stdout);

        /* 3. 자식 프로세스를 만들어 execvp()로 명령어를 실행한다 */
        pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(1);
        }
        if (pid == 0) {
            if (background) {
                printf("[%d] child process start\n", getpid());
                fflush(stdout);
            }
            execvp(args[0], args);
            exit(1);                      /* 실행 실패 */
        }

        /* 4. 부모는 자식이 끝나기를 기다린다 */
        child = wait(&status);
        if (background)
            printf("[%d] child process end %d\n", getpid(), child);

        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            printf("SUCCESS\n\n");
        } else {                          /* 없는 명령어면 끝낸다 */
            printf("Parent process end\n");
            printf("Exit\n");
            break;
        }
        /* 5. 맨 위로 돌아가서 반복 */
    }
    return 0;
}
