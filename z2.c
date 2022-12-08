#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <stdlib.h>

#define B 4.0
#define A -2.0

pthread_mutex_t key;
double res = 0, h;

double f(double x) {
	return 8 + 2 * x;
}

void *thread_function(void * arg) {
	int i = *(int*) arg;	
	pthread_mutex_lock(&key);
	res += f(A + h*(i + 0.5));
	pthread_mutex_unlock(&key);
}

int main(int argc, char **argv) {
	int p = 10;

    if (argc >= 2) 
	{
		p = atoi(argv[1]);
	}

	h = (B - A) / p;
	pthread_t *p_thread = malloc(sizeof(pthread_t) * p);
	
    pthread_mutex_init(&key, NULL);

	int i;
	for (i = 0; i < p; i++) {
		pthread_create(&p_thread[i], NULL, &thread_function, &i);		
	}

	for (i = 0; i < p; i++) {
		pthread_join(p_thread[i], NULL);
	}

	printf("Значение интеграла: %f\n", res * h); //Этот интеграл равен 60

	pthread_mutex_destroy(&key);
	free(p_thread);
}
