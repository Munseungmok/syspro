#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int fd, status;
    pid_t pid, child;

    /* 인자: ./main 출력파일 명령어 [명령어 인자...] */
    if (argc < 3) {
        fprintf(stderr, "usage: %s outfile command [args...]\n", argv[0]);
        exit(1);
    }

    pid = fork();
    if (pid < 0) {                 /* 자식 생성 실패 */
        perror("fork");
        exit(1);
    }

    if (pid == 0) {                /* ---- 자식 프로세스 ---- */
        fd = open(argv[1], O_CREAT | O_TRUNC | O_WRONLY, 0660);
        if (fd < 0) {
            perror("open outfile");
            exit(1);
        }
        if (dup2(fd, STDOUT_FILENO) < 0) {   /* 표준 출력을 파일로 변경 */
            perror("dup2");
            exit(1);
        }
        close(fd);                           /* 파일 디스크립터 닫기 */

        execvp(argv[2], &argv[2]);           /* 명령어 실행 */
        perror("execvp");                    /* 실패했을 때만 여기로 옴 */
        exit(1);
    }

    /* ---- 부모 프로세스 ---- */
    while ((child = wait(&status)) != pid) {
        if (child < 0 && errno != EINTR) {
            perror("wait");
            exit(1);
        }
    }

    if (WIFEXITED(status))
        printf("[%d] child process %d end\n", getpid(), pid);

    return 0;
}
