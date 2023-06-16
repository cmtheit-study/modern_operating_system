//
// Created by cmtheit on 23-6-16.
//

#include <pthread.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM (1 << 20)

bool if_prime(int num) {
    if (num < 2) {
        return false;
    }
    int up = (int)sqrt(num) + 1;
    for (int i = 2; i < up; ++i) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

typedef struct {
    int num;
} tester_param_s;

void * tester_rout(void * ppram) {
    tester_param_s param = *(tester_param_s *)ppram;
    int num = param.num;
    int tot = 0;
    for (int i = 2; i < (int)(sqrt(num) + 1); ++i) {
        if (if_prime(i)) {
            while (param.num % i == 0) {
//                printf("%d / %d = %d\n", param.num, i, param.num / i);
                param.num /= i;
                tot += i;
            }
            if (param.num == 1) {
                break;
            }
        }
    }
//    printf("%d - %d\n", tot, num);
    if (tot == num) {
        printf("%d \x1b[32m√\x1b[0m\n", num);
    }
}

int main() {
    tester_param_s * params = (tester_param_s *) malloc(sizeof (tester_param_s) * NUM);
    pthread_t * tester_pthread = (pthread_t *) malloc(sizeof(pthread_t) * NUM);
    for (int i = 0; i < NUM; ++i) {
        params[i].num = i + 1;
        pthread_create(tester_pthread + i, NULL, tester_rout, params + i);
    }
    for (int i = 0; i < NUM; ++i) {
        pthread_join(tester_pthread[i], NULL);
    }
    free(params);
    free(tester_pthread);
    return false;
}