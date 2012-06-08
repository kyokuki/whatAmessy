#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <errno.h>
void err_sys(const char *str)
{
    printf("%s\n", str);
    fflush(stdout);
    exit(1);
}

static void pr_ids(char *name)
{
    printf("%s: pid = %d, ppid = %d, pgrp = %d, tpgrp = %d, sid = %d\n",
           name, getpid(), getppid(), getpgrp(), tcgetpgrp(STDIN_FILENO), getsid(0));
    fflush(stdout);
}

int main(void)
{
    char c;
    pid_t pid;

    pr_ids("parent");
    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid > 0) {       /* parent */
        sleep(5);
        exit(0);
    } else {                    /* child */
        pr_ids("child");
        if ((pid = setsid()) < 0) {
            err_sys("setsid error");
        }
        pr_ids("setsid");
        if (read(STDIN_FILENO, &c, 1) != 1)
            printf("read erro form controlling TTY, errno = %d\n", errno);
        exit(0);
    }
}

