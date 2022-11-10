#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <malloc.h>

int f(int n)
{
	if (n == 0)
	{
		return 1;
	}

	int i, result = 1;

	for (i = 1; i <= n; i++)
	{
		result *= i;
	}

	return result;
}

void * catalan(void * arg)
{
	int i, n = *(int*) arg, * arr = malloc(sizeof(int) * n);

	for( i = 0; i < n; i ++)
	{
		arr[i] = f(2 * i) / (f(i + 1) * f(i));
	}

	return (void *) arr;
}

void * simple(void * arg)
{
	int numbers = 0, i = 2, n = *(int*) arg, * arr = malloc(sizeof(int) * n);

	while (numbers != n) 
	{
		int j, flag = 0;

		for (j = 2; j < i; j++)
		{
			if (i % j == 0)
			{
				flag = 1;
				break;
			}
		}

		if (flag == 0)
		{
			arr[numbers] = i;
			numbers++;
		}

		i++;
	}

	return (void *) arr;
}

int main(int argc, char * argv[])
{
	int n = atoi(argv[1]);

	pthread_t thread1;
	
	if (pthread_create(&thread1, NULL, &catalan, &n) != 0)
	{
		fprintf(stderr, "Error (thread1)\n");
		return 1;
	}

	int *catalanArray;

	pthread_join(thread1, (void *) &catalanArray); 

	pthread_t thread2;

	if (pthread_create(&thread2, NULL, &simple, &n) != 0)
	{
		fprintf(stderr, "Error (thread2)\n");
		return 1;
	}

	int *primeArray;

	pthread_join(thread2, (void *) &primeArray); 

	fprintf(stderr, "\n----------------------- CATALAN -----------------------\n");
	int i;

	for (i = 0; i < n; i++)
	{
		fprintf(stderr, "%d\n", catalanArray[i]);
	}

	fprintf(stderr, "\n----------------------- SIMPLE -----------------------\n");

	for (i = 0; i < n; i++)
	{
		fprintf(stderr, "%d\n", primeArray[i]);
	}
}
