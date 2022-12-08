#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

int * arr;

void * attr_function(void * thread_arg) {
    int i, n = *(int*) thread_arg;

    while(1)
    {
        sleep(1);

        for (i = 0; i < n; i++)
        {
            fprintf(stderr, "%d ", arr[i]);
        }

        fprintf(stderr, "\n");

        if (arr[n - 1])
        {
            break;
        }
    }
    
    return NULL;
}

void * thread_function(void * arg)
{
	int n = *(int*) arg;

	sleep(n);
    arr[n] = rand() % 10 + 1;

    sleep(arr[n]);

	return NULL;
}

int main(int argc, char *argv[]) {
    int n = 10, i;

    if (argc > 2)
	{
		n = atoi(argv[1]);
	}

    srand(time(NULL));

    pthread_attr_t attr;
    pthread_t attr_thread;

    pthread_attr_init (&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    pthread_create(&attr_thread, &attr, &attr_function, &n);
    
    pthread_t * thread = malloc(sizeof(pthread_t) * n);
    arr = malloc(sizeof(int) * n);
    
    for (i = 0; i < n; i++)
    {
        pthread_create(&thread[i], NULL, &thread_function, &i);
    }

    for (i = 0; i < n; i++)
    {
        pthread_join(thread[i], NULL);
    }

    pthread_attr_destroy(&attr);
    free(thread);
    free(arr);
}