#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

#define TIME 5

int main() 
{
    int counter = 0;

    time_t start;
    time_t finish;
    pid_t pid; /* идентификатор процесса */
    printf("Пока всего один процесс\n");

    printf("Вызов функции fork...\n");
    pid = fork(); /* Создание нового процесса */

    if (pid == 0) 
    {
        printf("Процесс - потомок\n");
    } 
    else if (pid > 0) 
    {
        printf("Родительский процесс, pid потомка %d\n", pid);
    } 
    else 
    {
        printf("Ошибка вызова fork, потомок не создан\n"); 
    }

    time(&start);
    while((difftime(finish, start)) < TIME)
    {
        time(&finish);
        counter++;
    }
    printf("Counter: %d\n", counter);
}