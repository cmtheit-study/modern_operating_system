//
// Created by cmtheit on 23-7-2.
//
#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main() {
    int fd = open("./test.txt", O_RDONLY);
    void * p = mmap(NULL, 10, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, sysconf(_SC_PAGESIZE));
    printf("first char: %c\n", *(char*)(p));
    *(char*)p = '1';
    close(fd);
    return 0;
}