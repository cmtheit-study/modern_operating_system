//
// Created by cmtheit on 23-7-4.
//

#include <unistd.h>

int main() {
    if (!fork()) {
        execl("./bad-prog.sh", "./bad-prog.sh", NULL);  // 并不会有什么作用
    }
}
