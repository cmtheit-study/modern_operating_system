#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int lock = 0;

int cnt = 0;

void * routine(void *) {
	while (lock);
	lock++;
	int pre = cnt;
    sleep(1);
    cnt = pre + 1;
	lock--;
}

int main() {
	int tot = 1000;
	pthread_t threads[tot];
	for (int i = 0; i < tot; ++i) {
		pthread_create(threads + i, NULL, routine, NULL);
	}
	for (int i = 0; i < tot; ++i) {
		pthread_join(threads[i], NULL);
	}
	printf("tot: %d\n", cnt);
	return 0;
}
