#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/socket.h>     /* for the socket's  */
#include <netinet/in.h>     /* for struct sockaddr_in */
#include <arpa/inet.h>      /* 处理字节序和网络字节序 */
#include <pthread.h>

#define MAXLINE 1024

void *handle(void *arg);

int main(void)
{
    char *ipstr = "127.0.0.1";

    struct sockaddr_in servaddr;
    struct sockaddr_in clientaddr;

    int listenfd;
    int connfd;
    int servport = 8888;
    int listenq = 1024;

    socklen_t socklen;
    pthread_t tid;

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    //inet_pton(AF_INET, ipstr, &servaddr.sin_addr);
    servaddr.sin_port = htons(servport);

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0) {
        perror("socket error");
        exit(1);
    }

    if (bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind error");
        exit(1);
    }

    if(listen(listenfd, listenq) < 0) {
        perror("listen error");
        exit(1);
    }

    printf("listening on port %d......\n", servport);

    for(;;) {
        connfd = accept(listenfd, (struct sockaddr *)&clientaddr, &socklen);
        if (connfd < 0) {
            perror("accept error");
            continue;
        }
        printf("accept from %s:%d...\n",inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

        int tidfd = connfd;
        if (pthread_create(&tid, NULL, handle, &tidfd) != 0) {
            perror("thread create error");
        }
    }
    return 0;
}

void *handle(void *arg)
{
    size_t n;
    char buf[MAXLINE];
    int fd = *(int *)arg;

    for(;;) {
        memset(buf, 0, MAXLINE);
        n = read(fd, buf, MAXLINE);
        if (n < 0) {
            perror("read error");
            break;
        }
        if (n == 0) {       /* if BLOCK：当连接关闭时,read返回0 .*/
            printf("client exit\n");
            break;
        }

        n = write(fd, buf, n);
        if (n ==0) {
            printf("client exit\n");
            break;
        }
        if (n < 0) {
            perror("write error");
            break;
        }
    }
    close(fd);
    pthread_exit(0);
}
