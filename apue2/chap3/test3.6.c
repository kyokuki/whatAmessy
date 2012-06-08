#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>
#include <unistd.h>

char buf[] = "1234567890";

int main()
{
    int fd;

    if ( (fd = open("tmp",O_CREAT | O_RDWR | O_TRUNC, 0600)) < 0) {
        fprintf(stderr, "file tmp open error(creat|rdwr).");
        exit(1);
    }
    
    if (write(fd, buf, 10) < 0) {
        fprintf(stderr, "file tmp write error");
        exit(1);
    }

    close(fd);



    if ( (fd = open("tmp",O_APPEND | O_RDWR)) < 0) {
        fprintf(stderr, "file tmp open error(append|rdwr).");
        exit(1);
    }
    
    if (lseek(fd, 0, SEEK_SET) < 0) {
        fprintf(stderr, "file tmp lseek  error(0 SEEK_SET).");
        exit(1);
    }    
    char buff[100];
    if (read(fd, buff, 5) < 0) {
        fprintf(stderr, "file tmp read error");
        exit(1);
    }
    buff[5] = '\0';
    printf("read from file tmp(SEEK_SET 0): %s\n",buff);


    if (lseek(fd, -5, SEEK_END) < 0) {
        fprintf(stderr, "file tmp lseek  error(-5 SEEK_END).");
        exit(1);
    }   
    if (read(fd, buff, 5) < 0) {
        fprintf(stderr, "file tmp read error");
        exit(1);
    } 
    buff[5] = '\0';
    printf("read from file tmp(SEEK_END -5): %s\n",buff);

   
    if (lseek(fd, 5, SEEK_END) < 0) {
        fprintf(stderr, "file tmp lseek  error(5 SEEK_END).");
        exit(1);
    }   
    if (read(fd, buff, 5) < 0) {
        fprintf(stderr, "file tmp read error");
        exit(1);
    } 
    buff[5] = '\0';
    printf("read from file tmp(SEEK_END 5): %s\n",buff);
   

    if (lseek(fd, 5, SEEK_SET) < 0) {
        fprintf(stderr, "file tmp lseek  error(5 SEEK_SET).");
        exit(1);
    }   
    if (write(fd, "abcde", 5) < 0) {
        fprintf(stderr, "file tmp write error");
        exit(1);
    } 

    close(fd);


}
