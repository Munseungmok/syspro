#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid;
    printf("[%d] Process start\n", (int)getpid());
    pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    }
    printf("[%d] Process : return value %d\n", (int)getpid(), (int)pid);
    return 0;
}
