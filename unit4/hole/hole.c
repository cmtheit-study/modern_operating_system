#include <stdio.h>

int main() {
    FILE * f = fopen("hole.txt", "w");
    fwrite("hello hole", 1, 10, f);
    fseek(f, 100, SEEK_CUR);    // 出现空洞
    fwrite("hello hole", 1, 10, f);
    fclose(f);
    remove("hole");
    return 0;
}