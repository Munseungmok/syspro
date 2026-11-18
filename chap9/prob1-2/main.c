#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid;
    pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    }
    if (pid == 0) {
        printf("[Child] : Hello, world pid=%d\n", (int)getpid());
    } else {
        printf("[Parent] : Hello, world pid=%d\n", (int)getpid());
    }
    return 0;
}
