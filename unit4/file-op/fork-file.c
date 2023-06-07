#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main() {
    int fd = open("./test.txt", O_RDONLY | O_CLOEXEC);
    if (fd > 0) {
        lseek(fd, 2, SEEK_CUR);
        if (!fork()) {
            printf("Child process has offset %d\n", lseek(fd, 0, SEEK_CUR));
        } else {
            printf("Father process has offset %d\n", lseek(fd, 0, SEEK_CUR));
        }
        close(fd);
    } else {
        printf("Cannot find test.txt\n");
    }
    unlink("fork-file");
    return 0;
}