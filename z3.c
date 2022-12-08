#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

void * thread_function(void * thread_arg) {
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
    
    int i, n = *(int*) thread_arg;

    for (i = 0; i < 2 * n; i++)
    {
        sleep(1);

        fprintf(stderr, "%d\n", i);
    }

    return NULL;
}

int main(int argc, char *argv[]) {
    int n = 10;

    if (argc > 2)
	{
		n = atoi(argv[1]);
	}
    
    pthread_t thread;
    void * flag;

    pthread_create(&thread, NULL, &thread_function, &n);

    sleep(n);
    pthread_cancel(thread);

    if (!pthread_equal(pthread_self(), thread))
    {
        pthread_join(thread, &flag);
    }

    if (flag == PTHREAD_CANCELED)
    {
        fprintf(stderr, "Отменен\n");
    }
    else
    {
        fprintf(stderr, "По-умолчанию\n");
    }
}