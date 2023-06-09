#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex;
int finish = 0;

int routine() {
    sleep(10);
    pthread_mutex_lock(&mutex);
    finish = 1;
    pthread_mutex_unlock(&mutex);
}

int main() {
    printf("begin test...\n");
    printf("Let's run this app.\n");
    pthread_mutex_init(&mutex, NULL);
    pthread_t pthread;
    pthread_create(&pthread, NULL, routine, NULL);
    int dot = 0;
    while (1) {
        pthread_mutex_lock(&mutex);
        if (finish) {
            pthread_mutex_unlock(&mutex);
            break;
        }
        printf("\x1b[1K");
        printf("\n");
        printf("\x1b[1A");
        printf("waiting");
        for (int i = 0; i < dot; ++i) {
            printf(".");
        }
        dot++;
        dot = dot > 3 ? 0 : dot;
        fflush(stdout);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    pthread_mutex_destroy(&mutex);
    return 0;
}