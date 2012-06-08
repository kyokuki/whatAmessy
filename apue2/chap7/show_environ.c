#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    extern char **environ;
    char **ptr =  NULL;

    for (ptr = environ; *ptr != NULL; ptr++) {
        printf("%s\n",*ptr);
    }
}
