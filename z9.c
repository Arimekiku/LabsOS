#include <unistd.h>
#include <stdio.h>
#include <sys/utsname.h>

int uname(struct utsname *name);
int gethostname(char *name, size_t namelen);
long gethostid(void);

int main()
{
    struct utsname computer;
    struct utsname *temp = &computer;

    uname(temp);

    char user[20];

    gethostname(user, 10);

    printf("id: %d\nname: %s\nrelease-date: %s\nOS-version: %s\ncomputer: %s", gethostid(), user, computer.release, computer.version, computer.machine);
}