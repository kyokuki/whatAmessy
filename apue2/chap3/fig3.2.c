#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define FILE_MODE		(S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main(void)
{
    int fd;

    if ((fd = creat("file.hole", FILE_MODE)) < 0)
        fprintf(stderr, "create error\n");

    if (write(fd, buf1, 10) != 10)
        fprintf(stderr, "buf1 write error\n");

    if (lseek(fd, 16384, SEEK_SET) == -1)
        fprintf(stderr, "lseek error\n");

    if (write(fd, buf2, 10) != 10)
        fprintf(stderr, "buf2 write error\n");

    exit(0);
}
