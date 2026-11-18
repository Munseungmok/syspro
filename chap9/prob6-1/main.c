#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid;
    printf("PARENT: PID = %d GID = %d\n", (int)getpid(), (int)getpgrp());

    pid = fork();
    if (pid == 0) {
        printf("CHILD: PID = %d GID = %d\n", (int)getpid(), (int)getpgrp());
    }
    return 0;
}
