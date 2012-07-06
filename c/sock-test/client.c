
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include <sys/socket.h>     /* for the socket's  */
#include <netinet/in.h>     /* for struct sockaddr_in */
#include <arpa/inet.h>      /* 处理字节序和网络字节序 */

#define MAXLINE 1024

void handle(int fd);

int main(void)
{
    char *ipstr = "127.0.0.1";
    struct sockaddr_in servaddr;

    int connfd;
    int servport = 8888;

    socklen_t socklen;

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, ipstr, &servaddr.sin_addr);
    servaddr.sin_port = htons(servport);

    connfd = socket(AF_INET, SOCK_STREAM, 0);
    if (connfd < 0) {
        perror("socket error.");
        exit(1);
    }

    if (connect(connfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("connect error.");
        exit(1);
    }

    printf("client started.....\n");
    printf("connected to %s:%d...\n",inet_ntoa(servaddr.sin_addr), ntohs(servaddr.sin_port));

    handle(connfd);

    return 0;
}

void handle(int fd)
{
    size_t n;
    char buf[MAXLINE];

    for(;;) {
        //memset(buf, 0, MAXLINE);
        if (fgets(buf, MAXLINE, stdin) == NULL) {
            break;
        }
        n = write(fd, buf, strlen(buf));
        if (n ==0) {
            break;
        }

    }
    close(fd);
}
