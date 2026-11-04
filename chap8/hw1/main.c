#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <-e [name] | -u | -g | -i | -p>\n", argv[0]);
        exit(1);
    }

    if (strcmp(argv[1], "-e") == 0) {
        if (argc == 2) {
            char **ptr;
            extern char **environ;
            for (ptr = environ; *ptr != 0; ptr++) {
                printf("%s\n", *ptr);
            }
        } else if (argc >= 3) {
            char *val = getenv(argv[2]);
            if (val != NULL) {
                printf("%s = %s\n", argv[2], val);
            } else {
                printf("%s = (null)\n", argv[2]);
            }
        }
    } 
    else if (strcmp(argv[1], "-u") == 0) {
        printf("My Realistic User ID : %d(%s)\n", getuid(), getpwuid(getuid())->pw_name);
        printf("My Valid User ID : %d(%s)\n", geteuid(), getpwuid(geteuid())->pw_name);
    } 
    else if (strcmp(argv[1], "-g") == 0) {
        printf("My Realistic Group ID : %d(%s)\n", getgid(), getgrgid(getgid())->gr_name);
        printf("My Valid Group ID : %d(%s)\n", getegid(), getgrgid(getegid())->gr_name);
    } 
    else if (strcmp(argv[1], "-i") == 0) {
        printf("my process number : [%d]\n", getpid());
    } 
    else if (strcmp(argv[1], "-p") == 0) {
        printf("my parent's process number : [%d]\n", getppid());
    } 
    else {
        fprintf(stderr, "Invalid option: %s\n", argv[1]);
        exit(1);
    }

    return 0;
}
