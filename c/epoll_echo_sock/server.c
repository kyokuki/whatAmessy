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
#include <sys/epoll.h>
#include <poll.h>

#define MAXLINE 1024
#ifndef EPOLL_MAX
#define EPOLL_MAX 1024
#endif

void handle(int fd, int eppollfd);

int main(void)
{
    int servport = 8888;
    int listenq = 1024;

    struct sockaddr_in servaddr, clientaddr;
    int listenfd, connfd;
    int nready;
    socklen_t socklen;

    int epollfd;
    struct epoll_event ev, events[EPOLL_MAX];

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

    epollfd = epoll_create(EPOLL_MAX);
    if (epollfd < 0) {
        perror("epoll create error");
        exit(1);
    }
    ev.events = POLLIN;
    ev.data.fd = listenfd;

    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, listenfd, &ev) == -1) {
        perror("epoll ctl error:listenfd");
        exit(1);
    }

    printf("server listening on port %d...\n", servport);
    printf("EPOLL_MAX = %d\n", EPOLL_MAX);

    int i;
    for (;;) {
        nready = epoll_wait(epollfd, events, EPOLL_MAX, -1);
        if (nready < 0) {
            perror("epoll wait error");
            continue;
        }

        for (i = 0; i < nready; i++) {
            if (events[i].data.fd == listenfd) {
                connfd = accept(listenfd, (struct sockaddr *)&clientaddr, &socklen);
                if (connfd < 0) {
                    perror("accept error");
                    continue;
                }
                printf("accept from %s:%d...\n",inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

                ev.events = POLLIN;
                ev.data.fd = connfd;
                if (epoll_ctl(epollfd, EPOLL_CTL_ADD, connfd, &ev) == -1) {
                    perror("epoll ctl error:connfd");
                    exit(1);
                }
            } else {
                handle(events[i].data.fd, epollfd);
            }
        }
    }
    close(epollfd);
    return 0;
}

void handle(int fd, int epollfd)
{
    size_t n;
    char buf[MAXLINE];
    struct epoll_event ev;


    if (fd < 0) {
        return;
    }
    n = read(fd, buf, MAXLINE);
    if (n < 0) {
        perror("read error");
        if (epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, &ev) == -1) {
            perror("epoll ctl error:del");
            exit(1);
        }
        close(fd);
    }

    if (n == 0) {
        printf("client closed.\n");
        if (epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, &ev) == -1) {
            perror("epoll ctl error:del");
            exit(1);
        }
        close(fd);
    }
    write(fd, buf, n);
}
