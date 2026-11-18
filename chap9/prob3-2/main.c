#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(void)
{
    pid_t pid;

    /* 1. 부모 프로세스 시작 출력 */
    printf("parental process start\n");

    /* 2. 첫 번째 자식: echo hello */
    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(1);
    }
    if (pid == 0) {
        execl("/bin/echo", "echo", "hello", (char *)NULL);
        fprintf(stderr, "execl echo failed\n");
        exit(1);
    }

    /* 3. 두 번째 자식: date */
    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(1);
    }
    if (pid == 0) {
        execl("/bin/date", "date", (char *)NULL);
        fprintf(stderr, "execl date failed\n");
        exit(1);
    }

    /* 4. 세 번째 자식: ls -l */
    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(1);
    }
    if (pid == 0) {
        execl("/bin/ls", "ls", "-l", (char *)NULL);
        fprintf(stderr, "execl ls failed\n");
        exit(1);
    }

    /* 5. 부모 프로세스 종료 출력 */
    printf("parental process end\n");

    return 0;
}
