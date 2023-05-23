#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int main() {
    char buf[1024] = {0};
    read(0, buf, 24);
    printf("%s\n", buf);
    return 0;
}