#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>


#define MAX_CNT 10

pthread_mutex_t mutex;
pthread_cond_t condp, condc;
int count = 0;
int container[MAX_CNT] = {0};

void * producer(void *) {
    while (true) {
        int item = rand();
        pthread_mutex_lock(&mutex);
        while (count == MAX_CNT) {
            printf("full\n");
            pthread_cond_wait(&condp, &mutex);
        }
        container[count++] = item;
        pthread_cond_signal(&condc);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
}

void * consumer(void *) {
    while (true) {
        pthread_mutex_lock(&mutex);
        while (!count) {
            printf("empty\n");
            pthread_cond_wait(&condc, &mutex);
        }
        printf("get item: %d\n", container[--count]);
        pthread_cond_signal(&condp);
        pthread_mutex_unlock(&mutex);
        sleep(2);
    }
}

int main() {
    pthread_t p, c;
    srand(time(NULL));
    pthread_cond_init(&condp, NULL);
    pthread_cond_init(&condc, NULL);
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);
    pthread_join(p, NULL);
    pthread_join(c, NULL);
    pthread_cond_destroy(&condp);
    pthread_cond_destroy(&condc);
    pthread_mutex_destroy(&mutex);
    return 0;
}