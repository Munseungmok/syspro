#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main() {
    pid_t pid1, pid2;
    int status, child;

    printf("[%d] parental process start\n", (int)getpid());
    
    pid1 = fork();
    if (pid1 == 0) {
        printf("[%d] child process[1] start\n", (int)getpid());
        sleep(1);
        printf("[%d] child process[1] end\n", (int)getpid());
        exit(1);
    }

    pid2 = fork();
    if (pid2 == 0) {
        printf("[%d] child process[2] start\n", (int)getpid());
        sleep(2);
        printf("[%d] child process[2] end\n", (int)getpid());
        exit(2);
    }

    child = waitpid(pid1, &status, 0);
    printf("[%d] child process[1] %d end\n", (int)getpid(), (int)child);
    printf("end code %d\n", status >> 8);
    
    waitpid(pid2, &status, 0);
    return 0;
}
