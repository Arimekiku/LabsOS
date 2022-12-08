#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <time.h>

static void signal_handler(int signo, siginfo_t *si, void *ucontext) {
    if (signo == SIGUSR1) {
        printf("Signal: %d - Value: %d Code: %d\n", signo, si->si_int, si->si_code);
    } else if (signo == SIGTERM) {
        printf("Finishing process...");
    } else {
        fprintf(stderr, "Неожиданный сигнал!\n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}

int main (int argc, char *argv[])
{
    if (argc < 2) //Если аргументов в командной строке мало то ошибка
	{
		fprintf(stderr, "Too few arguments\n");
		return 1;
	}
    int count = atoi(argv[1]);
    pid_t p = fork();

    if (p > 0) {
        struct sigaction acct;
        while(1) {
            acct.sa_sigaction = signal_handler;
            sigaction(SIGUSR1, &acct, NULL);
        }
    } else {
        int i;
        union sigval value;

        for (i = 0; i < count; i++) {
            value.sival_int = i;
            sigqueue(p, SIGUSR1, value);
        }

        while(p) {}    
    }
}