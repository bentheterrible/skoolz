#include <stdio.h>

void reverse(int *arr) {

	// Declare Variables
	int i, j, len = 32;;
	int temp[len];	

	// Copy array into a temp_array[]
	for (i = 0; i < len; i++) {
		temp[i] = arr[i];
	}
	
	// Place values of temp[] -> arr[] in reverse order	
	for (i = 0, j = 31; i < len; i++) {
		arr[i] = temp[j--];
	}	
	
	// Go back to where you came from!
	return;	
}

int main() {
	
	unsigned hex = 0x20010000;	
	int bin[32], i;

	for (i = 0; i < 32; i++) {
		bin[i] = hex&1;
		hex >>= 1;
	}
	
	for (i = 0; i < 32; i++) {
		printf("%d", bin[i]);
	}
	printf("\n");

	
	printf("%d %d %d %d %d %d \n", bin[31],  bin[30],  bin[29],  bin[28],  bin[27], bin[26]);  

		
}
