//
// Created by cmtheit on 23-7-5.
//

#include <stdio.h>

int main() {
    // 需要以 sudo 运行
    FILE * d = fopen("/dev/nvme0n1p1", "r");
    if (d) {
        printf("打开磁盘文件成功\n");
        const int buf_size = 512;
        unsigned char buf[buf_size];
        if (fread(buf, 1, buf_size, d) == buf_size) {
            printf("读取 %d 字节成功\n", buf_size);
            const int line_length = 16;
            for (int i = 0; i < buf_size / line_length; ++i) {
                for (int j = 0; j < line_length; ++j)
                    printf("%02x ", buf[j + i * line_length]);
                printf("\n");
            }
        }
        fclose(d);
    } else {
        printf("打开磁盘文件失败\n");
    }
}