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

int global = 0;

void visit() {
    int pre = global;
    sleep(1);
    global = pre + 5;
}

void * px_turn_routine(void * xp) {
    enum TurnType this_turn = *(int *)xp;
    enum TurnType other_turn = 1 - this_turn;
    while (turn == other_turn);
//
//        if (turn == other_turn) {
////            flags[this_turn] = false;   // 这两行代码只是让线程显得很有礼貌
////            flags[this_turn] = true;
//        }
    visit();
    printf("global: %d\n", global);
    turn = other_turn;
    sleep(4);
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