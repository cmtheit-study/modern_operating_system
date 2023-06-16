//
// Created by cmtheit on 23-6-16.
//

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>

int buffer = 0;
int should = 0;

#define CONSUMER_NUM 2

pthread_t producer_pthread;
pthread_t consumer_pthread[CONSUMER_NUM];
pthread_mutex_t should_mutex;

void * producer(void *) {
    while (true) {
        pthread_mutex_lock(&should_mutex);
        printf("Produce buffer. Buffer is %d to %d. Should be %d\n", buffer, buffer + 1, should + 1);

        buffer++;
        should++;
        pthread_mutex_unlock(&should_mutex);
        for (int i = 0; i < CONSUMER_NUM; ++i) {
            pthread_kill(consumer_pthread[i], SIGUSR1);
        }
    }
}

void sigkill() {

}

void * consumer(void *) {
    signal(SIGUSR1, sigkill);
    while (true) {
        // 互斥锁应该在此处获取，而非在 if 内部
        if (buffer > 0) {
            pthread_mutex_lock(&should_mutex);
            printf("Buffer %d minus 1 is %d. Should be %d\n", buffer, buffer - 1, should - 1);
            buffer--;
            should--;
            pthread_mutex_unlock(&should_mutex);
        } else {
            pause();
        }
    }
}

int main() {
    pthread_mutex_init(&should_mutex, NULL);
    pthread_create(&producer_pthread, NULL, producer, NULL);
    for (int i = 0; i < CONSUMER_NUM; ++i)
        pthread_create(consumer_pthread + i, NULL, consumer, NULL);
    pthread_join(producer_pthread, NULL);
    for (int i = 0; i < CONSUMER_NUM; ++i)
        pthread_join(consumer_pthread[i], NULL);
    pthread_mutex_destroy(&should_mutex);
    return 0;
}