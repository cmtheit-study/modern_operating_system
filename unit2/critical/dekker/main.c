//
// Created by cmtheit on 23-5-23.
//
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>

enum TurnType {
    p0,
    p1
};

enum TurnType turn = p0;

bool flags[2] = {false};
int global = 0;

void visit() {
    int pre = global;
    sleep(1);
    global = pre + 5;
}

void * px_turn_routine(void * xp) {
    enum TurnType this_turn = *(int *)xp;
    enum TurnType other_turn = 1 - this_turn;
    flags[this_turn] = true;
    while (flags[other_turn]) {             // 通过 flags 来实现只要对方完成了 visit，就一定可以使得自身能运行 visit，而非等待对方执行完其他代码再
        if (turn == other_turn) {
            flags[this_turn] = false;
            while (turn == other_turn);
            flags[this_turn] = true;
        }
    }
    visit();
    printf("global: %d\n", global);
    turn = other_turn;
    flags[this_turn] = false;
    sleep(1);
}

int main() {
    pthread_t pthread0, pthread1;
    enum TurnType turn0 = p0, turn1 = p1;
    pthread_create(&pthread0, NULL, px_turn_routine, &turn0);
    pthread_create(&pthread1, NULL, px_turn_routine, &turn1);
    pthread_join(pthread0, NULL);
    pthread_join(pthread1, NULL);
    printf("%d\n", global);
    return 0;
}