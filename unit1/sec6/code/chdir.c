#include <unistd.h>
#include <fcntl.h>

int main() {
    chdir("./newdir");
    int fd = open("sam.txt", O_RDONLY);
    char buf[10] = {0};
    read(fd, buf, 9);
    write(0, buf, 9);
    close(fd);
}