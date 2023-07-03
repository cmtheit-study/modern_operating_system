
#include <stdio.h>

int main(int argc, char *argv[]) {
    // argc表示命令行参数的数量，包括程序本身的名称
    // argv是一个指向字符串数组的指针，每个字符串表示一个命令行参数

    // 遍历所有命令行参数
    for (int i = 0; i < argc; i++) {
        printf("参数 %d: %s\n", i, argv[i]);
    }
    perror("java");

    return 0;
}
