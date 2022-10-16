#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

char *getenv(const char *name);

int main(int argc, char **argv)
{
    const struct option long_opt[] = {
        {"help", 0, 0, 'h'},
        {"name", 1, 0, 'n'},
        {NULL,0,NULL,0}
    };
    int option;
    char *name;

    if (argc == 1)
    {
        printf("./z5.out -n test");
        return 0;
    }

    while ((option = getopt_long(argc, argv, "n:h", long_opt, NULL)) != -1)
    {
        switch (option)
        {
        case 'h':
            printf("./z5.out -n test");
            return 0;
        case 'n':
            name = optarg;
            break;
        default:
            return 0;
        }
    }

    printf("%s", getenv(name));
}