#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int main() {
    pid_t child_pid;
    child_pid = fork();

    if (child_pid > 0) 
    {
        int status;
        sleep(2);

        system("ps -o stat,cmd");
        wait(&status);
        system("\nps -o stat,cmd");

        while(1) {}
    } 

    exit(0);
}