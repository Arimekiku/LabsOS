#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

pid_t getpid(void);

int main ()
{
    int increment = 0;
    pid_t p1, p2;

    // Запустим 2-х потомков
    if ((p1 = fork()) == 0) {
        increment++;
        printf("Первое поколение. pid: %d, increment: %d\n", getpid(), increment);

        // Запустим 2-х потомков
        pid_t p3, p4;
        if (p3 == fork() == 0)
        {
            increment++;
            printf("Второе поколение. pid: %d, increment: %d\n", getpid(), increment);
            exit(0);
        }

        if (p4 == fork() == 0)
        {
            increment++;
            printf("Второе поколение. pid: %d, increment: %d\n\n", getpid(), increment);
            exit(0);
        }

        exit(0);
    }

    if (p1 > 0 && (p2 = fork()) == 0) {
        increment++;
        printf("Первое поколение. pid: %d, increment: %d\n", getpid(), increment);

        // Запустим 2-х потомков
        pid_t p3, p4;
        if (p3 == fork() == 0)
        {
            increment++;
            printf("Второе поколение. pid: %d, increment: %d\n", getpid(), increment);
            exit(0);
        }

        if (p4 == fork() == 0)
        {
            increment++;
            printf("Второе поколение. pid: %d, increment: %d\n", getpid(), increment);
            exit(0);
        }

        exit(0);
    }
}