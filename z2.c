#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

struct thread_arg
{
	char * name; 
	char * string;
	int num;
};

void * any_func(void * arg)
{
	struct thread_arg * targ = (struct thread_arg*) arg;

	int i;
	for(i = 0; i < targ->num; i++)
	{
		printf("Thread %s. %s   Iteration: %d\n", targ->name, targ->string, i+1);	
	} 

	return NULL;
}

int main()
{
	char * test = "Test string";

	struct thread_arg arg1 = { "First", test, 1};
	pthread_t thread1;
	
	if(pthread_create(&thread1, NULL, &any_func, &arg1) != 0)
	{
		fprintf(stderr, "Error");
		return 1;
	}

	struct thread_arg arg2 = { "Second", test, 2};
	pthread_t thread2;

	if(pthread_create(&thread2, NULL, &any_func, &arg2) != 0)
	{
		fprintf(stderr, "Error");
		return 1;
	}

	struct thread_arg arg3 = { "Third", test, 3};
	pthread_t thread3;

	if(pthread_create(&thread3, NULL, &any_func, &arg3) != 0)
	{
		fprintf(stderr, "Error");
		return 1;
	}

	struct thread_arg arg4 = { "Fourth", test, 4};
	pthread_t thread4;

	if(pthread_create(&thread4, NULL, &any_func, &arg4) != 0)
	{
		fprintf(stderr, "Error");
		return 1;
	}

	sleep(3);
}
