#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int i;

    // 전달받은 모든 명령줄 인수를 인덱스와 함께 출력
    for (i = 0; i < argc; i++) {
        printf("argv[%d]: %s\n", i, argv[i]);
    }

    exit(0);
}
