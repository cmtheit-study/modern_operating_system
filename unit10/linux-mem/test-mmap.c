#include <sys/mman.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main() {
    int fd = open("file.txt", O_RDWR);  // 注意打开方式和映射方式要协调
    char * addr = mmap(
            NULL,
            sysconf(_SC_PAGESIZE),
            PROT_READ | PROT_WRITE,
            MAP_SHARED,
            fd, 0);
    if (addr == MAP_FAILED) {
        printf("创建内存映射失败: ");
        switch (errno) {
            case EINVAL:
                printf("无效");
                break;
            case ENOMEM:
                printf("无内存");
                break;
            case EBADF:
                printf("无效的文件描述符");
                break;
            case ENODEV:
                printf("文件映射不支持");
                break;
            case EACCES:
                printf("访问文件失败");
                break;
            case EAGAIN:
                printf("文件被锁住");
                break;
            default:
                printf("其他原因");
                break;
        }
        printf("\n");
        return 1;
    }
    printf("%c %c %c\n", addr[0], addr[1], addr[2]);
    *addr = 'j';
    printf("%c %c %c\n", addr[0], addr[1], addr[2]);
    msync(addr, sysconf(_SC_PAGESIZE), MS_SYNC);
    close(fd);
}