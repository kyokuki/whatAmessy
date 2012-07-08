
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include <sys/socket.h>     /* for the socket's  */
#include <netinet/in.h>     /* for struct sockaddr_in */
#include <arpa/inet.h>      /* 处理字节序和网络字节序 */

#define MAXLINE 1024
#define max(a,b)    ((a) > (b) ? (a) : (b))

void handle(int fd);

int main(void)
{
    char *ipstr = "127.0.0.1";
    struct sockaddr_in servaddr;

    int connfd;
    int servport = 8888;


    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, ipstr, &servaddr.sin_addr);
    servaddr.sin_port = htons(servport);

    connfd = socket(AF_INET, SOCK_STREAM, 0);
    if (connfd < 0) {
        perror("socket error");
        exit(1);
    }

    if (connect(connfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("connect error");
        exit(1);
    }

    printf("client started.....\n");
    printf("connected to %s:%d...\n",inet_ntoa(servaddr.sin_addr), ntohs(servaddr.sin_port));

    handle(connfd);
    close(connfd);
    return 0;
}

void handle(int fd)
{
    size_t n;
    struct timeval timeout;
    char sendbuf[MAXLINE];
    char recvbuf[MAXLINE];
    fd_set fdset;
    FILE * fp = stdin;
    int infd = fileno(fp);
    int maxfd = max(infd,fd);
    int nready;

    timeout.tv_sec = 0;
    timeout.tv_usec = 0;

    FD_ZERO(&fdset);


    for(;;) {
        FD_SET(fd, &fdset);
        FD_SET(infd, &fdset);

        nready = select(maxfd + 1, &fdset, NULL, NULL, NULL);
        if (nready < 0) {
            perror("select error");
            continue;
        }

        if (FD_ISSET(fd, &fdset)) {
            n = read(fd, recvbuf, MAXLINE);
            if (n < 0) {
                perror("read error");
                break;
            }
            else if (n == 0) {
                printf("closed by server.\n");
                break;
            }
            else {
                //printf(recvbuf);
                write(STDOUT_FILENO, recvbuf, n);
            }
        }

        if (FD_ISSET(infd, &fdset)) {
            memset(sendbuf, 0, MAXLINE);
            if (fgets(sendbuf, MAXLINE, fp) != NULL) {
                write(fd, sendbuf, strlen(sendbuf));
            }
        }
    }
}
