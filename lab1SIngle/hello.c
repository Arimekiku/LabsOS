#include <stdio.h>
#include <math.h>

double f(double x) {
	return exp(-fabs(x)) * sin(x);
}	

double g(double x) {
	return exp(-fabs(x)) * cos(x);
}

void main() {
	double x;
	scanf("%lf", &x);

	printf("f(x) = %f\ng(x) = %f\n", f(x), g(x));
}
