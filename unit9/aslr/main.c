//
// Created by cmtheit on 23-7-2.
//
#include <stdio.h>

int main() {
    printf("%p\n", main);   // main 函数地址每次运行都不一样，这是操作系统提供的 aslr
}