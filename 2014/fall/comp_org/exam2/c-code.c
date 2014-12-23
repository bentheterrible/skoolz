
int count_positive(int *a, int n) {
	int i = 0;
	int v = 0;

	while (n > 0) {
		if (a[i] > 0)
			v++;
		i++;
		n--;
	}
	return v;
}
