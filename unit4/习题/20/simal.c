#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    char * fn = "abc";
    int fd = open(fn, O_CREAT | O_WRONLY | O_TRUNC);
    write(fd, "abc", 3);
//    sync();
    int fd2 = open(fn, O_RDONLY);
    char buf[4] = {0};
    read(fd2, buf, 3);
    printf("read: %s\n", buf);
    close(fd2);
    close(fd);
    return 0;
}