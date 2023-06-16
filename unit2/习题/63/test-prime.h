//
// Created by cmtheit on 23-6-16.
//

#ifndef MODERN_OPERATING_SYSTEM_TEST_H
#define MODERN_OPERATING_SYSTEM_TEST_H

#define MAX_NUM (1 << 23)
#include <stdbool.h>
#include <math.h>
#include <stdio.h>

bool if_prime(int num) {
    int up = (int)sqrt(num) + 1;
    for (int i = 2; i < up; ++i) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

#endif //MODERN_OPERATING_SYSTEM_TEST_H
