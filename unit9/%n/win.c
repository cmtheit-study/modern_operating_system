#include <stdio.h>
#include <stdlib.h>
int main() {
    printf("0x%08x 0x%08x 0x%08x 0x%08x 0x%08x\n", 10);
    int s = 10;
    s *= rand();
    printf("%d\n", s);
}