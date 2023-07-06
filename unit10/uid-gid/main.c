//
// Created by cmtheit on 23-7-5.
//

#include <unistd.h>
#include <stdio.h>

int main() {
    printf("uid: %d; euid: %d\n", getuid(), geteuid());
    printf("gid: %d; egid: %d\n", getgid(), getegid());
    return 0;
}