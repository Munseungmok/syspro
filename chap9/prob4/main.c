#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main() {
    int status;

    status = system("date");
    if (status < 0) perror("system date");
    printf("end code %d\n", WEXITSTATUS(status));

    status = system("hello");
    if (status < 0) perror("system hello");
    printf("end code %d\n", WEXITSTATUS(status));

    status = system("who");
    if (status < 0) perror("system who");
    printf("end code %d\n", WEXITSTATUS(status));

    return 0;
}
