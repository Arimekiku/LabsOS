#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <math.h>

int n = 100000;
double currentPI = 0;

void * thread_function() {
    int i, divider = 1;
    int old_cancel_state;

    for (i = 0; i < n; i++)
    {
        pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &old_cancel_state);

        currentPI += pow(-1, i) * (1. / divider);
        divider += 2;

        pthread_setcancelstate(old_cancel_state, NULL);

        fprintf(stderr, "%lf\n", currentPI * 4);
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

    pthread_create(&thread, NULL, &thread_function, NULL);

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
        fprintf(stderr, "\n\nЧисло пи: %lf", currentPI * 4);
    }
}