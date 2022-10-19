#include <stdio.h>
#include <getopt.h>

int main(int argc, char **argv)
{
    char *filename = "standartFilename";
    int option;

    while ((option = getopt(argc, argv, "co:h")) != -1)
    {
        switch (option)
        {
        case 'h':
            printf("-h\n-o out_file_name\n-c special mode");
            return 0;
        case 'o':
            filename = optarg;
            break;
        case 'c':
            printf("You in special mode");
            break;
        default:
            return 0;
        }
    }

    fopen(filename, "w");
}