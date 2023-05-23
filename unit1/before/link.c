#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {

    link("test/origin.txt", "test/dest.txt");
    return 0;
}