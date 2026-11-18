#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int system(const char *cmd)
{
    pid_t pid;
    int status;

    if ((pid = fork()) < 0) {
        status = -1;
    } else if (pid == 0) {
        execl("/bin/sh", "sh", "-c", cmd, (char *)NULL);
        exit(127);
    } else {
        while (waitpid(pid, &status, 0) < 0) {
            if (errno != EINTR) {
                status = -1;
                break;
            }
        }
    }
    return status;
}

int main(void)
{
    int status;

    status = system("date");
    if (status < 0) perror("system date");
    printf("end code %d\n", WEXITSTATUS(status));

    status = system("hello");
    if (status < 0) perror("system hello");
    printf("end code %d\n", WEXITSTATUS(status));

    status = system("who; exit 44");
    if (status < 0) perror("system who");
    printf("end code %d\n", WEXITSTATUS(status));

    return 0;
}
