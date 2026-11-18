#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid1, pid2;
    printf("[PARENT] : Hello, world ! pid=%d\n", (int)getpid());
    
    pid1 = fork();
    if (pid1 == 0) {
        printf("[Child 1] : Hello, world ! pid=%d\n", (int)getpid());
        return 0;
    }
    
    pid2 = fork();
    if (pid2 == 0) {
        printf("[Child 2] : Hello, world ! pid=%d\n", (int)getpid());
        return 0;
    }
    
    return 0;
}
