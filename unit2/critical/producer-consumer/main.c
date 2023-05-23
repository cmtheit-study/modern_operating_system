#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>


#define MAX_CNT 10

pthread_mutex_t mutex;
int count = 0;
int container[MAX_CNT] = {0};

void * producer(void *) {
    while (true) {
        int item = rand();
        bool printed = false;
        while (count == MAX_CNT) {
            printf("full\n");
            if (!printed) {
                printed = true;
            }
        }
        pthread_mutex_lock(&mutex);
        container[count++] = item;
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
}

void * consumer(void *) {
    while (true) {
        while (!count);
        pthread_mutex_lock(&mutex);
        printf("get item: %d\n", container[--count]);
        pthread_mutex_unlock(&mutex);
        sleep(2);
    }
}

int main() {
    pthread_t p, c;
    srand(time(NULL));
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);
    pthread_join(p, NULL);
    pthread_join(c, NULL);
    pthread_mutex_destroy(&mutex);
    return 0;
}