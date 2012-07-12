#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>

static void sig_quit(int signo)
{
    printf("caught SIGQUIT...\n");
    if (signal(SIGQUIT, SIG_DFL) == SIG_ERR) {
        perror("can't reset SIGQUIT");
        exit(1);
    }
}

int main(void)
{
    sigset_t newmask, oldmask, pendmask;

    if (signal(SIGQUIT, sig_quit) == SIG_ERR) {
        perror("signal SIGQUIT error");
        exit(1);
    }

    sigemptyset(&newmask);
    sigaddset(&newmask, SIGQUIT);
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0) {
        perror("sigprocmask SIG_BLOCK error");
        exit(1);
    }
    printf("SIGQUIT blocked: 5 seconds\n");

    sleep(5);
    //raise(SIGQUIT);

    if (sigpending(&pendmask) < 0) {
        perror("sigpending error");
        exit(1);
    }
    if (sigismember(&pendmask, SIGQUIT)) {
        printf("\nSIG_QUIT pending\n");
    }

    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
        perror("sigprocmask SIG_SETMASK error");
        exit(1);
    }
    printf("SIGQUIT unblocked: 5 seconds\n");

    sleep(5);
    exit(0);

}
