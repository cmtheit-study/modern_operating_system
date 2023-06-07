//
// Created by cmtheit on 23-6-7.
//

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define BUF_SIZE 2048
#define MIN(a, b) ({ \
    typeof(a) _a = (a); \
    typeof(b) _b = (b); \
    _a < _b ? _a : _b; \
})

static inline void revert(char * src, size_t size) {
    for (int i = 0; i < size / 2; ++i) {
        char tmp = src[i];
        src[i] = src[size - i - 1];
        src[size - i - 1] = tmp;
    }
}

int main() {
    int test = open("test.txt", O_RDONLY);
    int tset = open("tset.txt", O_CREAT | O_WRONLY | O_TRUNC);
    fchmod(tset, S_IRUSR | S_IWUSR);
    if (test == -1 || tset == -1) {
        return 1;
    }
    long buffer_size = BUF_SIZE;
    char buffer[BUF_SIZE + 1] = {0};
    if (lseek(test, 0, SEEK_END) == -1) {
        printf("cannot seek 1\n");
        return 2;
    }
    for (;;) {
        long seeked = MIN(lseek(test, 0, SEEK_CUR), buffer_size);
        if (lseek(test, -seeked, SEEK_CUR) == -1) {
            printf("cannot seek 2\n");
            break;
        }
        ssize_t rd = read(test, buffer, seeked);
        if (rd) {
            revert(buffer, rd);
            write(tset, buffer, rd);
            printf("read %zd\n", rd);
            if (lseek(test, -rd, SEEK_CUR) == -1) {
                printf("cannot seek \n");
                break;
            }
        } else {
            break;
        }
    }
    close(test);
    close(tset);
    remove("main");
}