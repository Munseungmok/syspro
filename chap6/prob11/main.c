#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

void print_perm(mode_t mode) {
    char perm[11] = "----------";

    if (S_ISDIR(mode)) perm[0] = 'd';
    else if (S_ISLNK(mode)) perm[0] = 'l';
    else if (S_ISCHR(mode)) perm[0] = 'c';
    else if (S_ISBLK(mode)) perm[0] = 'b';
    else if (S_ISFIFO(mode)) perm[0] = 'p';
    else if (S_ISSOCK(mode)) perm[0] = 's';

    if (mode & S_IRUSR) perm[1] = 'r';
    if (mode & S_IWUSR) perm[2] = 'w';
    if (mode & S_IXUSR) perm[3] = (mode & S_ISUID) ? 's' : 'x';

    if (mode & S_IRGRP) perm[4] = 'r';
    if (mode & S_IWGRP) perm[5] = 'w';
    if (mode & S_IXGRP) perm[6] = (mode & S_ISGID) ? 's' : 'x';

    if (mode & S_IROTH) perm[7] = 'r';
    if (mode & S_IWOTH) perm[8] = 'w';
    if (mode & S_IXOTH) perm[9] = (mode & S_ISVTX) ? 't' : 'x';

    printf("%s ", perm);
}

int main(int argc, char *argv[]) {
    DIR *dp;
    struct dirent *dent;
    struct stat buf;
    struct passwd *pwd;
    struct group *grp;
    char path[1024];
    int opt_i = 0, opt_p = 0, opt_Q = 0;
    int opt;

    while ((opt = getopt(argc, argv, "ipQ")) != -1) {
        switch (opt) {
            case 'i':
                opt_i = 1;
                break;
            case 'p':
                opt_p = 1;
                break;
            case 'Q':
                opt_Q = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-i] [-p] [-Q] [directory]\n", argv[0]);
                exit(1);
        }
    }

    char *dir_path = ".";
    if (optind < argc) {
        dir_path = argv[optind];
    }

    if ((dp = opendir(dir_path)) == NULL) {
        perror("opendir()");
        exit(1);
    }

    while ((dent = readdir(dp)) != NULL) {
        snprintf(path, sizeof(path), "%s/%s", dir_path, dent->d_name);

        if (lstat(path, &buf) < 0) {
            perror("lstat()");
            continue;
        }

        printf("%4ld ", (long)(buf.st_blocks / 2));

        if (opt_i) {
            printf("%lu ", dent->d_ino);
        }

        print_perm(buf.st_mode);
        printf("%ld ", (long)buf.st_nlink);
        
        if ((pwd = getpwuid(buf.st_uid)) != NULL)
            printf("%s ", pwd->pw_name);
        else
            printf("%d ", buf.st_uid);

        if ((grp = getgrgid(buf.st_gid)) != NULL)
            printf("%s ", grp->gr_name);
        else
            printf("%d ", buf.st_gid);

        printf("%8ld ", (long)buf.st_size);

        char *t_str = ctime(&buf.st_mtime);
        if (t_str != NULL) {
            t_str[16] = '\0';
            printf("%s ", t_str + 4);
        }

        if (opt_Q) {
            printf("\"%s", dent->d_name);
            if (opt_p && S_ISDIR(buf.st_mode)) {
                printf("/");
            }
            printf("\"\n");
        } else {
            printf("%s", dent->d_name);
            if (opt_p && S_ISDIR(buf.st_mode)) {
                printf("/");
            }
            printf("\n");
        }
    }

    closedir(dp);

    return 0;
}
