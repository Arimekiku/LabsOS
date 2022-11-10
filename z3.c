#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> 

void * print_msg(void * arg) 
{
	int i, n = *(int*) arg;
	for (i = 0; i < n; i++)
	{
		printf("Message Tread. Iteration: %d\n", i);
		sleep(1);
	}

	pthread_exit(NULL);
}

void * any_func(void * arg) 
{
	int i, x, n = *(int*) arg;

	for (i = 0; i < n; i++) 
	{ 
		x = rand() % (n + 1);
		printf("Random: %d\n", x);	

		if (x == n) 
		{
			printf("Random number is equal to entered number! (%d)\n", n);
			pthread_exit(NULL);
		}
	}

	pthread_exit(NULL);
}

int main(int argc, char * argv[])
{
	int n = atoi(argv[1]);
	pthread_t thread1;
	
	if(pthread_create(&thread1, NULL, &print_msg, &n) != 0)
	{
		fprintf(stderr, "Error");
		return 1;
	}

	if(pthread_join(thread1, NULL) != 0)
	{
		fprintf(stderr, "Join error");
		return 1;
	}

	pthread_t thread2;

	if(pthread_create(&thread2, NULL, &any_func, &n) != 0)
	{
		fprintf(stderr, "Error");
		return 1;
	}

	if(pthread_join(thread2, NULL) != 0)
	{
		fprintf(stderr, "Join error");
		return 1;
	}

	fprintf(stderr, "Test message in main thread");
}
