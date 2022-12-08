#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#define MAX 5
#define MIN -5

static pthread_key_t thread_key;

void write_to_thread(const int number, const int counter)
{
    char * str = (char*) pthread_getspecific(thread_key);
    fprintf(stderr, "%d -- %s: %d\n", counter, str, number);
}

void * thread_function(void * arg)
{
	int n = *(int*) arg;
    sleep(n);

    char * str = "Какое-то сообщение, дальше случайное чилос";
    pthread_setspecific(thread_key, str);

    int numb = rand() % (MAX - MIN) + MIN;
    write_to_thread(numb, n + 1);

	return NULL;
}


int main(int argc, char *argv[]) {
    int n = 10, i;

    if (argc > 2)
	{
		n = atoi(argv[1]);
	}

    srand(time(NULL));

    pthread_key_create(&thread_key, NULL);
    pthread_t * thread = malloc(sizeof(pthread_t) * n);

    for (i = 0; i < n; i++)
    {
        pthread_create(&thread[i], NULL, &thread_function, &i);
    }

    for (i = 0; i < n; i++)
    {
        pthread_join(thread[i], NULL);
    }
}