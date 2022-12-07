#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

void system(char *str_to_run)
{
    pid_t child_pid;
    int index;
    char *args[] = { str_to_run, NULL };

    child_pid = fork();
    execv(args[0], args);

    if (child_pid > 0)
    {
        wait(&index);
    }
}

int main(int argc, char * argv[])
{
    char *str = argv[1];
    system(str);
}