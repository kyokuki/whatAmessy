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

#define MAXLINE 1024

void handle(int *fds, int maxfd, fd_set *rset, fd_set *allset);

int main(void)
{
    int servport = 8888;
    int listenq = 1024;

    struct sockaddr_in servaddr, clientaddr;
    struct timeval timeout;
    int listenfd, connfd;
    fd_set rset;
    fd_set allset;
    int maxfd;
    int clientfds[FD_SETSIZE];
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

    int i = 0;
    for(i=0; i<FD_SETSIZE; i++) {
        clientfds[i] = -1;
    }
    FD_ZERO(&allset);
    FD_SET(listenfd, &allset);
    rset = allset;
    maxfd = listenfd;

    printf("server listening on port %d...\n", servport);
    printf("FD_SETSIZE = %d\n", FD_SETSIZE);

    timeout.tv_sec = 0;
    timeout.tv_usec = 0;

    for (;;) {
        rset = allset;
        nready = select(maxfd + 1, &rset, NULL, NULL, NULL);
        if (nready < 0) {
            perror("select error");
            continue;
        }

        if (FD_ISSET(listenfd, &rset)) {
            connfd = accept(listenfd, (struct sockaddr *)&clientaddr, &socklen);
            if (connfd < 0) {
                perror("accept error");
                continue;
            }

            printf("accept from %s:%d...\n",inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

            for (i = 0; i < FD_SETSIZE; i++) {
                if (clientfds[i] == -1) {
                    clientfds[i] = connfd;
                    break;
                }
            }

            if (i == FD_SETSIZE) {
                fprintf(stderr, "too many connections : more than %d\n", FD_SETSIZE);
                close(connfd);
                continue;
            }

            if (maxfd < connfd) {
                maxfd = connfd;
            }

            FD_SET(connfd, &allset);
            if (--nready <= 0)
                continue;
        }

        handle(clientfds, maxfd, &rset, &allset);

    }



    return 0;
}

void handle(int *fds, int maxfd, fd_set *rset, fd_set *allset)
{
    size_t n;
    char buf[MAXLINE];
    int i;


    for(i = 0; i < maxfd; i++) {
        if (fds[i] == -1) {
            continue;
        }

        if (FD_ISSET(fds[i], rset)) {
            n = read(fds[i], buf, MAXLINE);
            if (n < 0) {
                perror("read error");
                FD_CLR(fds[i], allset);
                close(fds[i]);
                fds[i] = -1;
                continue;
            }

            if (n == 0) {
                printf("client closed.\n");
                FD_CLR(fds[i], allset);
                close(fds[i]);
                fds[i] = -1;
                continue;
            }
            write(fds[i], buf, n);
        }
    }
}
