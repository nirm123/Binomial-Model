#include <stdio.h>
#include <math.h>
#include <unordered_map>
#include <ctime>

#include <iostream>
using std::cout;
using std::endl;

using std::unordered_map;

#define true 1
#define false 0

double binomial_recurse(int n, double s, double u, double d, double r, double delta, double p, double k, int call, unordered_map<double, double>& mem, char exercise) {
	int american = false;
	double payoffU = 0;
	double payoffD = 0;
	double payoffT = 0;
	
	if (n == 0) {
		double payoff;
		if (call) {
			payoff = s - k;
			if (payoff > 0) {
				return payoff;
			} else {
				return 0;
			}
		} else {
			payoff = k - s;
			if (payoff > 0) {
				return payoff;
			} else {
				return 0;
			}
		}
	}
	if (american) {
		cout << "AMERICAN" << endl;
	}
	if (mem.count(s*n)) {
		return mem[s*n];
	}
	double fu = binomial_recurse(n - 1, s * u, u, d, r, delta, p, k, call, mem, exercise);
	double fd = binomial_recurse(n - 1, s * d, u, d, r, delta, p, k, call, mem, exercise);
	double f0 = exp(-1 * r * delta) * ((p * fu) + (1 - p) * fd);
	mem.insert({s*n, f0});
	return f0;
}

double binomial(char option, double k, double t, double s, double sigma, double r, double q, int n, char exercise) {
	double delta = t/n;
	//double u = exp(sigma * sqrt(delta));
	//double d = exp(-1 * sigma * sqrt(delta));
	double u = 1.2;
	double d = 0.8;
	
	double p = (exp((r - q) * delta) - d)/(u - d);

	

	unordered_map<double, double> memoize;

	if (option == 'P' || option == 'p') {
		return binomial_recurse(n, s, u, d, r, delta, p, k, false, memoize, exercise);
	}
	if (option == 'C' || option == 'c') {
		return binomial_recurse(n, s, u, d, r, delta, p, k, true, memoize, exercise);
	}
	return -1;
}

int main(void) {
	double temp = binomial('C', 1.5, 2, 1.5, 0.2, 0.05, 0.04, 2, 'E');
	printf("Price: %f\n", temp);

	/*
	clock_t begin = clock();
	double temp = binomial('C', 100, 1, 100, 0.2, 0.05, 0, 1000, 'E');
	clock_t end = clock();
	printf("Price: %f\n", temp);
	printf("Time: %f\n\n", double(end-begin) / CLOCKS_PER_SEC);
	begin = clock();
	temp = binomial('P', 100, 1, 100, 0.2, 0.05, 0, 1000, 'E');
	end = clock();
	printf("Price: %f\n", temp);
	printf("Time: %f\n", double(end-begin) / CLOCKS_PER_SEC);
	*/
	return 0;
}
