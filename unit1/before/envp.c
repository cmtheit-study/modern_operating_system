#include<stdio.h>

int main(int args, char * argv[], char ** envp) {	// 空指针结尾的字符串数组用来表示环境变量。
	if (envp) {
		while (*envp) {
			printf("%s\n", *envp);
			envp += 1;
		}
	}
	return 0;
}