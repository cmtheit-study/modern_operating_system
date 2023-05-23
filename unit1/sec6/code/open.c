#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>


int main() {
    int fd = open("sam.txt", O_RDONLY);
    char buf[1024] = {0};
    read(fd, buf, 20);
    write(0, buf, 20);
    close(fd);
    return 0;
}