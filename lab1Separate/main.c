#include <stdio.h>
#include "g.c"
#include "f.c"

void main() {
	double x;
	scanf("%lf", &x);

	printf("f(x) = %f\ng(x) = %f\n", f(x), g(x));
}
