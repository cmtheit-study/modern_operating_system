#include<stdio.h>
#include <stdlib.h>
#include<pthread.h>

void * print_self_stack(void * va) {
	int vac = *(int *)va;
	printf("%p %p\n", &va, &vac);
}

int main() {
	int thread_num = 10;
	pthread_t threads[thread_num];
	int thread_args[thread_num];
	for (int i = 0; i < thread_num; ++i) {
		pthread_create(threads + i, NULL, print_self_stack, thread_args + i);
	}	
	for (int i = 0; i < thread_num; ++i) {
		pthread_join(threads[i], NULL);
	}
	return 0;
}
