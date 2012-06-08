#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <signal.h>

//extern char *sys_siglist[];

int sig2str(int signo, char *str)
{
    strcpy(str, sys_siglist[signo]);
    //printf("%d : %s\n", signo, str);
    return 0;
}


int main(void)
{
    char buf[1024];
    
    sig2str(SIGINT, buf);
    sig2str(SIGALRM, buf);
}
