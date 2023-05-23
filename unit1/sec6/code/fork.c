#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int global = 10;

int main() {
    printf("Main: My pid is %d, my global is %d\n", getpid(), global);
    for (int i = 0; i < 10; ++i) {
        int child_pid = fork();
        if (child_pid == 0) {
            global += 100;
            printf("Child: My PID is %d, my global is %d\n", getpid(), global);
            return i;
        } else {
            int child_status;
            // waitpid(-1, &child_status, 0); 
            // printf("My child status is %d\n", child_status);
            printf("Main: My child pid is %d my global is %d\n", child_pid, global);
        }
    }
}