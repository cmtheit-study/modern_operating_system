//
// Created by cmtheit on 23-7-4.
//
#include <unistd.h>
#include <stdio.h>
#include <sys/resource.h>

int main() {
    struct rlimit data_rlm;
    getrlimit(RLIMIT_DATA, &data_rlm);
    printf("数据段大小限制：%lx\n", data_rlm.rlim_max);
    if (brk((void *)0x52fe7d783000) == 0) {
        printf("seg number is %p\n", sbrk(0));
    }
}