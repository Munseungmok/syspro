#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main() {
    pid_t pid;
    int status, child;

    printf("[%d] parental process strat\n", (int)getpid());
    pid = fork();
    if (pid == 0) {
        printf("[%d] child process start\n", (int)getpid());
        exit(1);
    }
    
    child = wait(&status);
    printf("[%d] child process %d end\n", (int)getpid(), (int)child);
    printf("end code %d\n", status >> 8);
    return 0;
}
