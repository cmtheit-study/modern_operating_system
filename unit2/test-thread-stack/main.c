#include<stdio.h>
#include <stdlib.h>
#include<pthread.h>
#include <errno.h>

void * print_self_stack(void * va) {
	int vac = *(int *)va;
	printf("%p %p\n", &va, &vac);
}

int main() {
	int thread_num = 10;
	pthread_t threads[thread_num];
	int thread_args[thread_num];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    void * stack_start = (void *)0x7f34a0000000;
    int stack_size = (1 << 30) + (1);
	for (int i = 0; i < thread_num; ++i) {
        #if _POSIX_C_SOURCE >= 200112L
            if (pthread_attr_setstacksize(&attr, stack_size)) {
                switch (errno) {
                    case EINVAL:
                        printf("EINVAL\n");
                        break;
                    case EACCES:
                        printf("EACCES\n");
                        break;
                    default:
                        printf("other error\n");
                        break;
                }
                exit(1);
            }
            stack_start -= stack_size;
        #endif
		pthread_create(threads + i, &attr, print_self_stack, thread_args + i);
	}	
	for (int i = 0; i < thread_num; ++i) {
		pthread_join(threads[i], NULL);
	}
	return 0;
}
