//
// Created by cmtheit on 23-6-16.
//

#include <pthread.h>
#include "test-prime.h"
#define THREAD_NUM 10000

bool tested[MAX_NUM] = {false};


pthread_mutex_t tested_mutex;
pthread_t pthreads[THREAD_NUM];

void * test_rout(void * start) {
    int the_num = *(int*)start;
    while (the_num < MAX_NUM) {
        pthread_mutex_lock(&tested_mutex);
        if (tested[the_num]) {
            pthread_mutex_unlock(&tested_mutex);
            break;
        } else {
            tested[the_num] = true;
            pthread_mutex_unlock(&tested_mutex);
            if_prime(the_num);
            the_num++;
        }
    }
}

int main() {
    pthread_mutex_init(&tested_mutex, NULL);
    int starts[THREAD_NUM];
    for (int i = 0; i < THREAD_NUM; ++i) {
        starts[i] = MAX_NUM / THREAD_NUM * i;
        pthread_create(pthreads + i, NULL, test_rout, starts + i);
    }
    for (int i = 0; i < THREAD_NUM; ++i) {
        pthread_join(pthreads[i], NULL);
    }
    pthread_mutex_destroy(&tested_mutex);
    return 0;
}