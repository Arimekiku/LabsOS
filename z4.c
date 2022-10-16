#include <stdio.h>
#include <stdlib.h>

extern char **environ;

int main()
{
    printf("%s", environ);
}