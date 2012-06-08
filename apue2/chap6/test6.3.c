#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>

int main(void)
{
    struct utsname uts;
    
    if (uname(&uts) < 0) {
        fprintf(stderr,"uname error\n");
        exit(1);
    }

    printf("utsname.sysname = %s\n", uts.sysname );
    printf("utsname.nodename = %s\n", uts.nodename );
    printf("utsname.release = %s\n", uts.release );
    printf("utsname.version = %s\n", uts.version );
    printf("utsname.machine = %s\n", uts.machine );
}
