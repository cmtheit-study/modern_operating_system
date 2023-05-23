#include "pth.h"

int main() {
    pthread_attr_t addr;
    pthread_attr_init(&addr);
    printf("hello make file\n");
    return 0;
}