#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    printf("parental process start\n");
    
    pid = fork();
    if (pid == 0) {
        if (execl("/bin/echo", "echo", "hello", NULL) == -1) {
            fprintf(stderr, "execl failed\n");
            exit(1);
        }
    } else if (pid > 0) {
        wait(NULL);
        printf("prarental process end\n");
    } else {
        perror("fork");
    }
    return 0;
}
