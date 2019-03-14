#include <stdio.h>
#include <math.h>
#include <time.h>

#define true 1
#define false 0

double binomial(char option, double k, double t, double s, double sigma, double r, double q, int n, char exercise) {
	double delta = t/n;
	//double u = exp(sigma * sqrt(delta));
	//double d = exp(-1 * sigma * sqrt(delta));
	double u = 2;
	double d = 0.5;
	double p = (exp((r - q) * delta) - d)/(u - d);
	
	double f[n + 1];

	int i, j;
	double early_exercise;

	for (i = 0; i < n + 1; i++) {
		f[i] = pow(u, i) * pow(d, n - i) * s;
		if (option == 'P' || option == 'p') {
			f[i] = k - f[i];
		}
		if (option == 'C' || option == 'c') {
			f[i] = f[i] - k;
		}
		if (f[i] < 0) {
			f[i] = 0;
		}
	}

	for (i = n; i > 0; i--) {
		for (j = 0; j < i; j++) {
			f[j] = exp(-1 * r * delta) * ((p * f[j+1]) + (1 - p) * f[j]);
			if (exercise == 'A' || exercise == 'a') {
				early_exercise = pow(u, j) * pow(d, i - j - 1) * s;
				if (option == 'P' || option == 'p') {
					early_exercise = k - early_exercise;
				}
				if (option == 'C' || option == 'c') {
					early_exercise = early_exercise - k;
				}
				if (early_exercise > f[j]) {
					f[j] = early_exercise;
				}			
			}
		}
	}

	return f[0];
}

int main(void) {
	clock_t begin = clock();
	double temp = binomial('P', 5, 2, 4, 0.2, log(1.25), 0, 2, 'A');
	clock_t end = clock();
	printf("Price: %f\n", temp);
	printf("Time: %f\n\n", (double)(end-begin) / CLOCKS_PER_SEC);
	
	/*
	clock_t begin = clock();
	double temp = binomial('C', 100, 1, 100, 0.2, 0.05, 0.04, 5000, 'E');
	clock_t end = clock();
	printf("Price: %f\n", temp);
	printf("Time: %f\n\n", (double)(end-begin) / CLOCKS_PER_SEC);
	*/

	/*
	clock_t begin = clock();
	double temp = binomial('C', 100, 1, 100, 0.2, 0.05, 0, 1000, 'E');
	clock_t end = clock();
	printf("Price: %f\n", temp);
	printf("Time: %f\n\n", (double)(end-begin) / CLOCKS_PER_SEC);
	begin = clock();
	temp = binomial('P', 100, 1, 100, 0.2, 0.05, 0, 1000, 'E');
	end = clock();
	printf("Price: %f\n", temp);
	printf("Time: %f\n", (double)(end-begin) / CLOCKS_PER_SEC);
	*/
	return 0;
}
