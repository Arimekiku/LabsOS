#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

double atof(const char *string);

void doubleEq(double a, double b, double c){
	double d = pow(b, 2) - 4 * a * c, x1, x2;

	if (d < 0) 
	{
		printf("Undefined solution");
		return;
	} 

	if (d == 0) 
	{
		x1 = -b / (2 * a);

		printf("x = %lf\n", x1);
		return;
	} 

	x1 = (-b + sqrt(d))/(2 * a);
	x2 = (-b - sqrt(d))/(2 * a);

	printf("x1 = %lf\nx2 = %lf\n", x1, x2);
}

int main(int argc, char *argv[]){
	int i;
	char abc[3] = "abc";
	
	printf("Your parametres: a = %s b = %s c = %s\n SOLUTION\n", argv[1], argv[2], argv[3]);

    double a = atof(argv[1]);
    double b = atof(argv[2]);
    double c = atof(argv[3]);

    doubleEq(a, b, c);
}
