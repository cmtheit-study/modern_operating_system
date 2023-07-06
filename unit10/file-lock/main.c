//
// Created by cmtheit on 23-7-5.
//
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>

int main() {
    int fd = open("./f.txt", O_RDWR);
    if (fd != -1) {
        printf("打开文件成功\n");
        struct flock fl;
        memset(&fl, 1, sizeof (fl));
        fl.l_start = 1;
        fl.l_whence = L_SET;
        fl.l_len = 3;
        fl.l_type = F_WRLCK;
        fl.l_pid = getpid();
        printf("加锁结果：%d\n", fcntl(fd, F_SETLK, &fl));
        printf("阻塞加锁结果：%d\n", fcntl(fd, F_SETLKW, &fl));  // 同一进程不受限制
        sleep(1);
        printf("解锁\n");
        fcntl(fd, F_UNLCK);
        close(fd);
    }
}