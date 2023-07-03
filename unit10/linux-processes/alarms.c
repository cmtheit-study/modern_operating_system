//
// Created by cmtheit on 23-7-4.
//
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

void sigalarm() {
    printf("receive SIGALARM.\n");
}

int main() {
    alarm(1);
    printf("Last alarm remains %ds\n", alarm(2));   // 后一个 alarm 调用会覆盖前一个
    signal(SIGALRM, sigalarm);
    int slp_t = 3;
    printf("Slept %ds\n", slp_t - sleep(slp_t));
    alarm(1);
    alarm(0);   // 传入 0 会立即取消
    sleep(1);
    alarm(2);
    pause();            // pause 系统调用等待 alarm 信号
    return 0;
}