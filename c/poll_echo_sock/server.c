#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include <unistd.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <poll.h>

#define MAXLINE 1024
#ifndef POLL_MAX
#define POLL_MAX 1024
#endif

void handle(struct pollfd *pollfds , int maxfd);

int main(void)
{
    int servport = 8888;
    int listenq = 1024;

    struct sockaddr_in servaddr, clientaddr;
    int listenfd, connfd;
    struct pollfd pollfds[POLL_MAX];
    int maxfd;
    int nready;
    socklen_t socklen;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0) {
        perror("socket error");
        exit(1);
    }

    int opt = 1;
    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("setsockopt error");
        exit(1);
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(servport);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(listenfd,(struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind error");
        exit(1);
    }

    if (listen(listenfd, listenq) < 0) {
        perror("listen error");
        exit(1);
    }

    pollfds[0].fd = listenfd;
    pollfds[0].events = POLLIN;
    int i;
    for (i = 1; i < POLL_MAX; i++) {
        pollfds[i].fd = -1;
    }
    maxfd = listenfd + 1;

    printf("server listening on port %d...\n", servport);
    printf("POLL_MAX = %d\n", POLL_MAX);


    for (;;) {
        nready = poll(pollfds, POLL_MAX, -1);
        if (nready < 0) {
            perror("select error");
            continue;
        }

        if (pollfds[0].revents & POLLIN) {
            connfd = accept(listenfd, (struct sockaddr *)&clientaddr, &socklen);
            if (connfd < 0) {
                perror("accept error");
                continue;
            }

            printf("accept from %s:%d...\n",inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

            for (i = 1; i < POLL_MAX; i++) {
                if (pollfds[i].fd == -1) {
                    pollfds[i].fd = connfd;
                    pollfds[i].events = POLLIN;
                    break;
                }
            }

            if (i == POLL_MAX) {
                fprintf(stderr, "too many connections : more than %d\n", POLL_MAX);
                close(connfd);
                continue;
            }

            if (maxfd < connfd) {
                maxfd = connfd + 1;
            }

            if (--nready <= 0)
                continue;
        }

        handle(pollfds , maxfd);
    }



    return 0;
}

void handle(struct pollfd *pollfds , int maxfd)
{
    size_t n;
    char buf[MAXLINE];
    int i;


    for(i = 1; i < maxfd; i++) {
        if (pollfds[i].fd == -1) {
            continue;
        }

        if (pollfds[i].revents & POLLIN) {
            n = read(pollfds[i].fd, buf, MAXLINE);
            if (n < 0) {
                perror("read error");
                close(pollfds[i].fd);
                pollfds[i].fd = -1;
                pollfds[i].events &= 0;
                continue;
            }

            if (n == 0) {
                printf("client closed.\n");
                close(pollfds[i].fd);
                pollfds[i].fd = -1;
                pollfds[i].events &= 0;
                continue;
            }
            write(pollfds[i].fd, buf, n);
        }
    }
}
