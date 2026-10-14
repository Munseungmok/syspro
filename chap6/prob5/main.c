#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

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

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
        exit(1);
    }

    if ((dp = opendir(argv[1])) == NULL) {
        perror("opendir()");
        exit(1);
    }

    while ((dent = readdir(dp)) != NULL) {
        snprintf(path, sizeof(path), "%s/%s", argv[1], dent->d_name);

        if (lstat(path, &buf) < 0) {
            perror("lstat()");
            continue;
        }

        printf("%4ld ", (long)(buf.st_blocks / 2));
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

        printf("%s\n", dent->d_name);
    }

    closedir(dp);

    return 0;
}
