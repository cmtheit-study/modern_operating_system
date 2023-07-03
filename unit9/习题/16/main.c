//
// Created by cmtheit on 23-7-3.
//

#include <stdio.h>
#include <stdlib.h>

char trans(char alpha, int move) {
    return 'a' <= alpha && alpha <= 'z' ? ((alpha - 'a' + move) % ('z' - 'a' + 1) + 'a'): alpha;
}

int main() {
    FILE * input = fopen("input.en", "r");
    if (!input) {
        printf("Cannot open file.\n");
        return 1;
    }
    char * buf;
    fseek(input, 0, SEEK_END);
    size_t len = ftell(input);
    buf = malloc(len);
    fseek(input, 0, SEEK_SET);
    fread(buf, 1, len, input);
    fclose(input);
    for (int i = 1; i < 'z' - 'a'; ++i) {
        printf("move: %d\n", i);
        for (int j = 0; j < len; ++j) {
            printf("%c", trans(buf[j], i));
        }
        printf("\n");
    }
}