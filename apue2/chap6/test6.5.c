#include <stdio.h>
#include <stdlib.h>

#include <time.h>


int main(void)
{
    time_t timet;
    struct tm *tm = NULL;
    char buf[1024];

    if (time(&timet) < 0) {
        fprintf(stderr, "time function error\n");
        exit(1);
    }
    
    tm = localtime(&timet);
    if (tm == NULL) {
        fprintf(stderr, "localtime function error\n");
        exit(1);
    }
    
    strftime(buf, 1024, "%a %b %e %T %Z %Y",tm);
    
    printf("%s\n", buf);
}
