#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <getopt.h>

#define TIME 2
#define COUNT_W 5
#define COUNT_R 10

int *array;
pthread_rwlock_t rwlock;

void *detached_thread_func (void *arg) {
    int size = *(int*) arg;

    int i;
    while (1) {
        sleep(TIME);
        
        fprintf(stderr, "\n");

        for (i = 0; i < size; i++){
            fprintf(stderr, "%d ", array[i]);
        }  

        fprintf(stderr, "\n\n");
    }

    pthread_exit(NULL);
}

void *writer_thread_func (void *arg) {
    int n = *(int*) arg;

    while (1) {
        pthread_rwlock_wrlock(&rwlock);
        int r = rand() % n;
        int value = rand() % 9 + 1;
        if (array[r] == 0) {
            array[r] = value;
            fprintf(stderr, "Записано в %d-й индекс, значение: %d\n", r, array[r]);
        }
        pthread_rwlock_unlock(&rwlock);

        sleep(r);
    }

    pthread_exit(NULL);
}

void *reader_thread_func (void *arg) {
    int n = *(int*) arg;

    while (1) {
        pthread_rwlock_rdlock(&rwlock);
        int r = rand() % n;
        if (array[r] != 0) {
            fprintf(stderr, "Прочитано из %d-го индекса, значение: %d\n", r, array[r]);
            array[r] = 0;  
        }
        pthread_rwlock_unlock(&rwlock);

        sleep(r);
    } 

    pthread_exit(NULL);
}

int main(int argc, char *argv[]){
    srand(time(NULL));

    int n = 10, i, opt;

    while ((opt = getopt(argc, argv, "s:")) != -1){
        switch(opt) {
            case 's':
                n = atoi(optarg);
                break;
        }
    }

    array = malloc(sizeof(int) * n);

    pthread_attr_t attr;
    pthread_t pt;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_create(&pt, &attr, &detached_thread_func, &n);
    
    pthread_t *writers = malloc(sizeof(pthread_t) * COUNT_W), *readers = malloc(sizeof(pthread_t) * COUNT_R); 
    pthread_rwlock_init(&rwlock, NULL);

    for (i = 0; i < COUNT_R; i++) {
        pthread_create(&readers[i], NULL, &reader_thread_func, &n);

        if (i < COUNT_W) {
            pthread_create(&writers[i], NULL, &writer_thread_func, &n);
        }
    }
        
    for(i = 0; i < COUNT_R; ++i) {
        pthread_join(readers[i], NULL);

        if (i < COUNT_W) {
            pthread_join(writers[i], NULL);
        }
    }

    pthread_attr_destroy(&attr);
    pthread_rwlock_destroy(&rwlock);
    free(array);
    free(writers);
    free(readers);
}