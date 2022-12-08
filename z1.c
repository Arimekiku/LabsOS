#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

#define WORK_SIZE 1024
#define MIN -5
#define MAX 5

void *consumer_thread(void *arg);
void *conductor_thread(void *arg);

sem_t conductor_sem;
sem_t consumer_sem;
sem_t sem;

int *arr, currentN = 0, n = 10;

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

    sem_init(&conductor_sem, 1, 0);
    sem_init(&consumer_sem, 1, n);
    sem_init(&sem, 1, 1);

    pthread_create(&consumer, NULL, consumer_thread, NULL);
    pthread_create(&conductor, NULL, conductor_thread, NULL);

    sleep(time);

    pthread_cancel(conductor);
    pthread_cancel(consumer);

    exit(EXIT_SUCCESS);
}

void *consumer_thread(void *arg) {
    while (1) {
        sleep(2);
        sem_wait(&conductor_sem);
        sem_wait(&sem);

        arr[currentN] = 0;
        currentN--;

        sem_post(&sem);
        sem_post(&consumer_sem);
        
        int i;
        for (i = 0; i < currentN; i++) {
            fprintf(stderr, "%d ", arr[i]);
        }

        fprintf(stderr, " - Поглощено\n");
    }

    pthread_exit(NULL);
}

void *conductor_thread(void *arg) {
    while (1) {
        sleep(1);
        int numb = rand() % (MAX - MIN) + MIN; 

        sem_wait(&consumer_sem);
        sem_wait(&sem);

        arr[currentN] = numb;
        currentN++;

        sem_post(&conductor_sem);
        sem_post(&sem);

        int i;
        for (i = 0; i < currentN; i++) {
            fprintf(stderr, "%d ", arr[i]);
        }

        fprintf(stderr, " - Произведено\n");
    }

    pthread_exit(NULL);
}