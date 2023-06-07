#include <stdio.h>
#include <syscall.h>
#include <unistd.h>

int main() {
    syscall(__NR_creat, "hello.c");
    syscall(__NR_unlink, "hello.c");
    remove("create");
    return 0;
}