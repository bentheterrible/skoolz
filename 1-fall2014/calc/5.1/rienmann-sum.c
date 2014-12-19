#include <stdio.h>
#include <math.h>

double power(double n) {
	return n*n;
}

double foo(double n) {
	
	return 7 * power(n) + 7*n;
}

int main() {
	
	double i;
	double result = 0;
	
	for (i = -2; i <= 0; i++) {
		result += foo(i);
	}
	printf("%.4lf\n", result);
}
