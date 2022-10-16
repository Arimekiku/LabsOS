#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>

int clearenv(void);
extern char **environ;

int main(int argc, char **argv)
{
    const struct option long_opt[] = {
        {"help", 0, 0, 'h'},
        {"name", 1, 0, 'n'},
        {NULL,0,NULL,0}
    };
    int option;
    char *name;

    while ((option = getopt_long(argc, argv, "n:h", long_opt, NULL)) != -1)
    {
        switch (option)
        {
        case 'h':
            printf("./z7.out --n test");
            return 0;
        case 'n':
            name = optarg;
            break;
        default:
            return 0;
        }
    }

    if (name)
    {
        unsetenv(name);   
    }
    else
    {
        clearenv();
    }

    printf("%s", environ);
}