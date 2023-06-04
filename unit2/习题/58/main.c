#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#define BUFFER_SIZE 10

typedef int data_t;
typedef size_t semaphore;

semaphore buffer_size = 0;

pthread_mutex_t data_mutex; // 数据互斥锁

pthread_cond_t condp;   // 生产者条件变量
pthread_cond_t condc;   // 消费者条件变量
data_t datas[BUFFER_SIZE];

void mysleep(size_t milli) {
    clock_t before = clock();
    while ((clock() - before) * 1.0 / CLOCKS_PER_SEC * 1000 < milli);
}

void * consumer(void *) {
    while (true) {
        pthread_mutex_lock(&data_mutex);
        while (!buffer_size) {
            pthread_cond_wait(&condc, &data_mutex);
        }
        buffer_size--;
        printf("get data: %d\n", datas[buffer_size]);
        if (buffer_size == BUFFER_SIZE - 1) {
            pthread_cond_signal(&condp);
        }
        pthread_mutex_unlock(&data_mutex);
        mysleep(rand() % 10000);
    }
}

void * producer(void *) {
    while (true) {
        pthread_mutex_lock(&data_mutex);
        while (buffer_size == BUFFER_SIZE) {
            pthread_cond_wait(&condp, &data_mutex);
        }
        buffer_size++;
        datas[buffer_size - 1] = rand() % 256;
        printf("produce data: %d\n", datas[buffer_size - 1]);
        if (buffer_size == 1) {
            pthread_cond_signal(&condc);
        }
        pthread_mutex_unlock(&data_mutex);
        mysleep(rand() % 10000);
    }
}

int main() {
    srand(time(NULL));
    int producer_num = 10;
    int consumer_num = 20;
    pthread_t producers [producer_num];
    pthread_t consumers[consumer_num];
    pthread_mutex_init(&data_mutex, NULL);
    pthread_cond_init(&condp, NULL);
    pthread_cond_init(&condc, NULL);
    for (int i = 0; i < producer_num; ++i) {
        pthread_create(producers + i, NULL, producer, NULL);
    }
    for (int i = 0; i < consumer_num; ++i) {
        pthread_create(consumers + i, NULL, consumer, NULL);
    }
    for (int i = 0; i < producer_num; ++i) {
        pthread_join(producers[i], NULL);
    }
    for (int i = 0; i < consumer_num; ++i) {
        pthread_join(consumers[i], NULL);
    }
    pthread_mutex_destroy(&data_mutex);
    pthread_cond_destroy(&condp);
    pthread_cond_destroy(&condc);

}