#include <stdio.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

/* 프로세스의 실제/유효 사용자 ID와 그룹 ID를 출력한다. */
int main(void) {
    printf("My Realistic User ID: %d(%s)\n", getuid(), getpwuid(getuid())->pw_name);
    printf("My Valid User ID: %d(%s)\n", geteuid(), getpwuid(geteuid())->pw_name);
    printf("My Realistic Group ID: %d(%s)\n", getgid(), getgrgid(getgid())->gr_name);
    printf("My Valid Group ID: %d(%s)\n", getegid(), getgrgid(getegid())->gr_name);

    return 0;
}
