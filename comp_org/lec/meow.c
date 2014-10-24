#include <stdio.h>

int main() {

	//	hello 
	int row, col;
	double var;
	for(row = 1; row <= 20; row++) {
		for(col = 1; col <= 12; col++) {

			fscanf(ifp, "input.txt", &var);
			printf("%d\t", var);
		}	
		printf("\n");
	}	
}
