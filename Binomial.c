#include <stdio.h>
#include <math.h>
#include <time.h>

#define true 1
#define false 0

/*
 * binomial
 *   DESCRIPTION: Uses the binomial model to generate accurate call/put price
 *   INPUTS: option - P: Put option
 *   		      C: Call option
 *   	     k - Strike price
 *   	     t - Time period
 *   	     s - Asset price (current)
 *   	     sigma - Volatility
 *   	     r - Risk free interest rate
 *   	     q - Asset yield
 *   	     n - Number of steps (intervals) for model
 *   	     exercise - E: European option
 *   	                A: American option
 *   OUTPUTS: Option price
 *   RETURN VALUE: Double representing the option price
 *   SIDE EFFECTS: None
 */
double binomial(char option, double k, double t, double s, double sigma, double r, double q, int n, char exercise) {
	/* Calculate delta - time per interval */
	double delta = t/n;
	
	/* Calculate u and d base on Cox-Ross-Rubinstein binomial model */
	double u = exp(sigma * sqrt(delta));
	double d = exp(-1 * sigma * sqrt(delta));
	
	/* Calculate risk neautral probability */
	double p = (exp((r - q) * delta) - d)/(u - d);
	
	/* Declare array for storing forward prices */
	double f[n + 1];

	/* Declare variables for loop */
	int i, j;

	/* Declare variable for calculating early exercise payoffs for American options */
	double early_exercise;

	/* For loop to initialize array with last interval data */
	for (i = 0; i < n + 1; i++) {
		/* Stock price at node formula*/
		f[i] = pow(u, i) * pow(d, n - i) * s;

		/* Calculate payoff if put option */
		if (option == 'P' || option == 'p') {
			f[i] = k - f[i];
		}

		/* Calculate payoff if call option */
		if (option == 'C' || option == 'c') {
			f[i] = f[i] - k;
		}

		/* Payoff always greater than 0 */
		if (f[i] < 0) {
			f[i] = 0;
		}
	}

	/* For loop to complete backwards induction */
	for (i = n; i > 0; i--) {
		/* Loop through intercal */
		for (j = 0; j < i; j++) {
			/* Risk neutral pricing formula */
			f[j] = exp(-1 * r * delta) * ((p * f[j+1]) + (1 - p) * f[j]);
			
			/* If American option, need to check if early_exercis is optimal */
			if (exercise == 'A' || exercise == 'a') {
				/* Stock price at node formula */
				early_exercise = pow(u, j) * pow(d, i - j - 1) * s;

				/* Calculate payoff if put option */
				if (option == 'P' || option == 'p') {
					early_exercise = k - early_exercise;
				}

				/* Calculate payoff if call option */
				if (option == 'C' || option == 'c') {
					early_exercise = early_exercise - k;
				}

				/* If early exercise payoff is greater, choose early exercise */
				if (early_exercise > f[j]) {
					f[j] = early_exercise;
				}			
			}
		}
	}

	/* Return option price */
	return f[0];
}

/* main */
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
