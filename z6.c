#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

int setenv(const char *name, const char *value, int overwrite);
char *getenv(const char *name);

int main(int argc, char **argv)
{
    const struct option long_opt[] = {
        {"help", 0, 0, 'h'},
        {"value", 1, 0, 'v'},
        {"name", 1, 0, 'n'},
        {NULL,0,NULL,0}
    };
    int option;
    char *name, *value;
    
    if (argc == 1)
    {
        printf("./z6.out --n test --v test");
        return 0;
    }

    while ((option = getopt_long(argc, argv, "n:h:v", long_opt, NULL)) != -1)
    {
        switch (option)
        {
        case 'h':
            printf("./z6.out --n test --v test");
            return 0;
        case 'n':
            name = optarg;
            break;
        case 'v':
            value = optarg;
            break;
        default:
            return 0;
        }
    }

    if (value == NULL || name == NULL)
    {
        printf("Name or value was not setted!");
        return 0;
    }

    setenv(name, value, 0);
    printf("%s - %s", name, getenv(name));
}