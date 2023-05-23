#include <stdio.h>
#include <stdlib.h>


int main(int argc, char * argv[]) {
	printf("&argc = 0x%x\n", (unsigned)&argc);
	static int st = 100;
	static int st2 = 200;
	printf("&st = 0x%x, &st2 = 0x%x\n", (unsigned)&st, (unsigned)&st2);
	void * heap = malloc(1);
	printf("&heap = 0x%x\n", (unsigned)heap);
// 	main(argc, argv);
	return 0;
}