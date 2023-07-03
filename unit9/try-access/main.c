//
// Created by cmtheit on 23-7-2.
//

#include <stdio.h>
#include <unistd.h>

int main() {
    const char * fn = "rd.txt";
    if (!access(fn, R_OK | X_OK)) {
        printf("I can read and execute%s.\n", fn);
    } else {
        printf("I cannot read and execute %s\n", fn);
    }
    return 0;
}