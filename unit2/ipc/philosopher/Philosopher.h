//
// Created by cmtheit on 23-5-24.
//

#ifndef MODERN_OPERATING_SYSTEM_PHILOSOPHY_H
#define MODERN_OPERATING_SYSTEM_PHILOSOPHY_H

#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>

#define Philosophy_Num 5


enum PhilosopherState {
    thinking,
    eating,
};

typedef struct Philosopher {
    size_t id;
    enum PhilosopherState state;
    pthread_t pthread;
    pthread_cond_t cond;
} Philosopher;

extern pthread_mutex_t philosophers_mutex;
extern Philosopher philosophers[Philosophy_Num];



void philosophers_init();
void * philosopher_run(void * p);

Philosopher * philosopher_left(Philosopher * p);
Philosopher * philosopher_right(Philosopher * p);
void philosopher_think(Philosopher * p);
void philosopher_eat(Philosopher * p);
void philosopher_take_forks(Philosopher * p);
void philosopher_put_forks(Philosopher * p);

void philosophers_destroy();

#endif //MODERN_OPERATING_SYSTEM_PHILOSOPHY_H
