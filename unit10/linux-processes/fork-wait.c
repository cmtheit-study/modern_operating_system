//
// Created by cmtheit on 23-7-3.
//

#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int pid = fork();
    if (pid > 0) {
        int loc = 0;
        printf("等待子进程\n");
        int p = waitpid(-1, &loc, 0);
        printf("子进程 %d 退出: %d\n", p, loc >> 8);
    } else if (pid == 0) {
        printf("子进程运行...\n");
        sleep(1);
        printf("子进程退出\n");
        exit(10);
    } else {
        printf("创建子进程失败\n");
    }
}