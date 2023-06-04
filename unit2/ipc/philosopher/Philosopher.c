//
// Created by cmtheit on 23-5-24.
//

#include "Philosopher.h"
#include <stdio.h>

Philosopher philosophers[Philosophy_Num];
pthread_mutex_t philosophers_mutex;

void philosophers_init() {
    pthread_mutex_init(&philosophers_mutex, NULL);
    for (size_t i = 0; i < Philosophy_Num; ++i) {
        philosophers[i].id = i;
        philosophers[i].state = thinking;
        pthread_create(&philosophers[i].pthread, NULL, philosopher_run, philosophers + i);
        pthread_cond_init(&philosophers[i].cond, NULL);
    }
}

void * philosopher_run(void * p) {
    Philosopher * P = (Philosopher*) p;
    while (true) {
        philosopher_take_forks(P);
        sleep(1);
        philosopher_put_forks(P);
        sleep(1);
    }
}

Philosopher * philosopher_left(Philosopher * p) {
    return p->id == 0 ? (philosophers + Philosophy_Num - 1) : (philosophers + p->id - 1);
}

Philosopher * philosopher_right(Philosopher * p) {
    return p->id == (Philosophy_Num - 1) ? philosophers : (philosophers + p->id - 1);
}

void philosopher_think(Philosopher * p) {
    p->state = thinking;
    printf("p%lu thinking...\n", p->id);
}

void philosopher_eat(Philosopher * p) {
    p->state = eating;
    printf("p%lu eating...\n", p->id);
}

void philosopher_take_forks(Philosopher * p) {
    pthread_mutex_lock(&philosophers_mutex);
    if (philosopher_left(p)->state == eating || philosopher_right(p)->state == eating) {
        pthread_cond_wait(&p->cond, &philosophers_mutex);
    }
    philosopher_eat(p);
    pthread_mutex_unlock(&philosophers_mutex);
}

void philosopher_put_forks(Philosopher * p) {
    pthread_mutex_lock(&philosophers_mutex);
    philosopher_think(p);
    if (philosopher_left(p)->state == thinking) {
        pthread_cond_signal(&philosopher_left(p)->cond);
    }
    if (philosopher_right(p)->state == thinking) {
        pthread_cond_signal(&philosopher_right(p)->cond);
    }
    pthread_mutex_unlock(&philosophers_mutex);
}

void philosophers_destroy() {
    for (size_t i = 0; i < Philosophy_Num; ++i) {
        pthread_join(philosophers[i].pthread, NULL);
        pthread_cond_destroy(&philosophers[i].cond);
    }
    pthread_mutex_destroy(&philosophers_mutex);
}
