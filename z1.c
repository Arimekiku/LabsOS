#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <pthread.h>

int n = 0; 

void * inc_thread_function(void * thread_arg) { 
    sleep(rand() % 5);

    int i, number = *(int*) thread_arg;

    for (i = 0; i < number; i++)
    {
        n++;
    }

    fprintf(stderr, "Number: %d\n", n);
    
    return NULL;
}

void * dec_thread_function(void * arg) { 
    sleep(rand() % 5);

	int i, number = *(int*) arg; 

	for (i = 0; i < number; i++)
    {
        n--;
    }

    fprintf(stderr, "Number: %d\n", n);

	return NULL;
}

int main(int argc, char *argv[]) {
    srand(time(NULL));

    int threads = 2, number = 5;
    int opt;
    pthread_t *inc_thread, *dec_thread;

    while ((opt = getopt(argc, argv, "n:t:")) != -1)
    {
        switch (opt)
        {
        case 't': 
            threads = atoi(optarg);
            break;
        case 'n': 
            number = atoi(optarg);
            break;
        }
    }
    
    inc_thread = malloc (sizeof(pthread_t) * threads);
    dec_thread = malloc (sizeof(pthread_t) * threads);

    int i;
    for (i = 0; i < threads; i++) {
        pthread_create(&inc_thread[i], NULL, &inc_thread_function, &number);
        pthread_create(&dec_thread[i], NULL, &dec_thread_function, &number);
    }

    for (i = 0; i < threads; i++) {
        pthread_join(inc_thread[i], NULL);
	    pthread_join(dec_thread[i], NULL);
    }

    fprintf(stderr, "Result Number: %d", n);
    
    return 0;
}