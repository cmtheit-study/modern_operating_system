#include <unistd.h>
#include <stdio.h>
#include <memory.h>

int func(int a, int b) {
    memset(&a, 0, b);
    printf("%d, %d\n", a, b);
    return 10;
}

int main() {
    func(0xffffeeee, 5);
}