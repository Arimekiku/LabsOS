#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

#define MIN -5
#define MAX 5

void *consumer_thread(void *arg);
void *conductor_thread(void *arg);
void set_thread_flag (int flag_value);
void initialize_flag();

int *arr, currentN = 0, n, thread_flag;

pthread_mutex_t thread_flag_mutex;

int main(int argc, char *argv[]) {
    srand(time(NULL));

    int time = 5;
    if (argc >= 3) 
	{
		time = atoi(argv[1]);
        n = atoi(argv[2]);
	}
    arr = malloc(sizeof(int) * n);

    pthread_t conductor, consumer;
    void *thread_result;

    initialize_flag();

    pthread_create(&consumer, NULL, consumer_thread, NULL);
    pthread_create(&conductor, NULL, conductor_thread, NULL);

    sleep(time);

    pthread_cancel(conductor);
    pthread_cancel(consumer);

    exit(EXIT_SUCCESS);
}

void *consumer_thread(void *arg) {
    while (1) {
        int flag_is_set;

        pthread_mutex_lock(&thread_flag_mutex);
        flag_is_set = thread_flag;
        pthread_mutex_unlock(&thread_flag_mutex);

        if (flag_is_set) {
            arr[currentN] = 0;
            currentN--;

            int i;
            for (i = 0; i < currentN; i++) {
                fprintf(stderr, "%d ", arr[i]);
            }

            fprintf(stderr, " - Поглощено\n");

            set_thread_flag(0);
        }
    }

    pthread_exit(NULL);
}

void *conductor_thread(void *arg) {
    while (1) {
        sleep(2);
        int numb = rand() % (MAX - MIN) + MIN; 

        arr[currentN] = numb;
        currentN++;

        int i;
        for (i = 0; i < currentN; i++) {
            fprintf(stderr, "%d ", arr[i]);
        }

        fprintf(stderr, " - Произведено\n");

        set_thread_flag(1);
    }

    pthread_exit(NULL);
}

void set_thread_flag (int flag_value) {
    pthread_mutex_lock (&thread_flag_mutex);
    thread_flag = flag_value;
    pthread_mutex_unlock (&thread_flag_mutex);
}

void initialize_flag () {
    pthread_mutex_init (&thread_flag_mutex, NULL);
    thread_flag = 0;
}