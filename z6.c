#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

int counter = 0;

void cancel_function(void * buffer)
{
    fprintf(stderr, "Поток был отменен на %d итерации.\n", *(int*) buffer);
}

void * thread_function() {
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

    void * temp_buffer = &counter;
    pthread_cleanup_push(cancel_function, temp_buffer);

    while(1)
    {
        sleep(1);

        fprintf(stderr, "%d\n", counter);

        counter++;
    }

    pthread_cleanup_pop(0);

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
        fprintf(stderr, "По-умолчанию\n");
    }
}