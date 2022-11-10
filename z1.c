#include <pthread.h> 
#include <stdio.h> 
#include <unistd.h> 

void * any_func(void * args) 
{
	int i;
	for(i = 0; i < 10; i ++) 
	{
		printf("Child Thread. Iteration: %d\n", i + 1);
		sleep(1); 
	}

	return NULL;
}

int main()
{
	pthread_t thread;
	int i, result = pthread_create(&thread, NULL, &any_func, NULL);
	
	if (result != 0) 
	{
		fprintf(stderr, "Error\n");
		return 1;
	}

	for (i = 0; i < 10; i ++) 
	{
		printf("Main Thread. Iteration: %d\n", i + 1);
		sleep(1); 
	}

	while(1);
}
