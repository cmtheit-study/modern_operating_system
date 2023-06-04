#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

typedef int data_t;
typedef size_t semaphore;
pthread_mutex_t mutex;
pthread_mutex_t writer_mutex;
pthread_cond_t cond;
semaphore reading = 0;
semaphore writing = 0;
data_t data = 0;

void * reader(void*) {
    while (true) {
        pthread_mutex_lock(&mutex);
        reading++;
        pthread_mutex_unlock(&mutex);
        printf("read: %d\n", data);
        pthread_mutex_lock(&mutex);
        reading--;
        if (reading == 0) {
            pthread_cond_signal(&cond);
        }
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
}

void * writer(void*) {
    while (true) {
        pthread_mutex_lock(&writer_mutex);
        while (reading) {
            pthread_cond_wait(&cond, &writer_mutex);
        }
        data = rand() % 256;
        pthread_mutex_unlock(&writer_mutex);
        sleep(1);
    }
}

int main() {
    size_t readers_num = 10;
    pthread_t readers[readers_num];
    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&writer_mutex, NULL);
    pthread_cond_init(&cond, NULL);
    for (int i = 0; i < readers_num; ++i) {
        pthread_create(readers + i, NULL, reader, NULL);
    }
    pthread_t writer_p;
    pthread_create(&writer_p, NULL, writer, NULL);
    pthread_join(writer_p, NULL);
    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&writer_mutex);
    pthread_cond_destroy(&cond);
    return 0;
}