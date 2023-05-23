#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <time.h>

int childprocess(int until) {
	static int cnt = 0;	// 静态变量被也精确复制到子进程中。即使这在多线程中是不安全的。
	time_t last = time(NULL);
	while(1)  {
		if (time(NULL) - last >= 1) {
			cnt ++;
			last = time(NULL);
			printf("Child %u called %d times\n", getpid(), cnt);
		}
		if (cnt >= until) {
			break;
		}
	}
	execve("/bin/ls", NULL, NULL);
	return 10;
}

int fatherprocess(int child) {
	static int cnt = 0;
	time_t last = time(NULL);
	while(1)  {
		if (time(NULL) - last >= 1) {
			cnt ++;
			last = time(NULL);
			printf("Father %u called %d times\n", getpid(), cnt);
		}
		if (cnt >= 5) break;
	}
	int stat = 0;
	waitpid(child, &stat, 0);
	printf("Child stat: %d\n", stat);
	return 1;
}

int main() {
	int pid1 = fork();
	if (pid1 == 0) {
		printf("In child process\n");
		childprocess(10);
		return 10;
	} else if (pid1 > 0) {
		printf("Create child process %d\n", pid1);
		int pid2 = fork();
		if (pid2 == 0) {
			printf("In other child process\n");
			childprocess(25);
			return 20;
		} else if (pid2 > 0) {
			printf("Create child process %d\n", pid2);
			fatherprocess(-1);
			fatherprocess(pid1);
		} else {
			printf("Create child process error.");
			return 1;
		}
	} else {
		printf("Create child process error.");
		return 1;
	}
	return 0;
}