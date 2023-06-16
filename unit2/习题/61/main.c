//
// Created by cmtheit on 23-6-16.
//

#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

int turn = 0;
int max_turn = 10;

int next_turn() {
    return (turn + 1) % max_turn;
}

void * rout(void * n) {
    int the_turn = *(int*)n;
    while (true) {
        while (turn != the_turn);
        printf("turn %d\n", the_turn);
        turn = next_turn();
        sleep(1);
    }
}

int main() {
    printf("hello world");
    pthread_t pthreads[max_turn];
    int n_turns[max_turn];
    for (int i = 0; i < max_turn; ++i) {
        n_turns[i] = i;
        pthread_create(pthreads + i, NULL, rout, n_turns + i);
    }
    for (int i = 0; i < max_turn; ++i) {
        pthread_join(pthreads[i], NULL);
    }
}
