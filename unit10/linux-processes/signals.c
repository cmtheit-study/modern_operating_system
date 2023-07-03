//
// Created by cmtheit on 23-7-4.
//

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void report_pid_pgid() {
    printf("pid: %d, pgid: %d\n", getpid(), getpgrp());
}

int main() {
    report_pid_pgid();
    int pid;
    if (!(pid = fork())) {
        struct sigaction sa;
        sa.sa_handler= report_pid_pgid;
        sigaction(SIGUSR1, &sa, NULL);
        printf("Set sigaction\n");
        sleep(10); // sleep 函数接收信号会提前结束
        printf("Sub process exit normally.\n");
    } else {
        sleep(1);
        kill(pid, SIGUSR1);
        printf("Kill sub process %d\n", pid);
    }
}