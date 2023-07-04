//
// Created by cmtheit on 23-7-4.
//
#define _GNU_SOURCE
#include <unistd.h>
#include <sched.h>
#include <stdio.h>
#include <sys/mman.h>

int child(__attribute__((unused)) void * _) {
    printf("child running with:\n");
    printf("\t tid: %d\n", gettid());
    printf("\t pid: %d\n", getpid());
    return 0;
}

int main() {
    const int stack_size = 1024 * 1024;
    void * stack = mmap(NULL, stack_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_STACK, -1, 0);
    void * stack_top = stack + stack_size;
    child(NULL);
    // 与 fork 效果类似
    clone(child, stack_top, CLONE_VFORK, NULL);
    // 与 pthread_create 效果类似
    clone(child, stack_top, CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_THREAD | CLONE_VFORK, NULL);
}