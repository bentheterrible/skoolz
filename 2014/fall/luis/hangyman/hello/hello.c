#include <stdio.h>

int main() {
	printf("hello\n");	

	int *ptr = NULL;
	int x = 2;

	printf("%p\n", x);

	*ptr = 2;
}
