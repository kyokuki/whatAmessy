#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(void)
{
    time_t timet;
    time_t tmp;

    if (time(&timet) < 0) {
        fprintf(stderr, "time functon error\n");
        exit(1);
    }

    tmp = tmp&0x0;
    tmp = ~tmp;
    tmp = tmp & 0x7FFFFFFF ;
    //tmp = tmp << 1;

    printf("time_t now : %X\n", timet);
    printf("time now : %s\n", ctime(&timet));
    
    printf("time_t max : %X\n", tmp);
    printf("time max : %s\n", ctime(&tmp));
}
