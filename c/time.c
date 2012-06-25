#include <stdio.h>
#include <time.h>

#define LEN 512

int main(void)
{

    time_t timet;
    struct tm *timetm1 = NULL;
    struct tm *timetm2 = NULL;
    char buf[LEN] = {0,};

    timet = time(NULL);
    
    
    printf("%ju secs since the Epoch\n", timet);
    timetm1 = localtime(&timet); /* 日历时间-->本地时间 */
    printf("asctime local tm : %s", asctime(timetm1));
    timetm2 = gmtime(&timet);    /* 日历时间-->国际标准时间  */
    printf("asctime gm tm : %s", asctime(timetm2));
    printf("ctime : %s", ctime(&timet));


    //printf("timetm1 = %ju\n", timetm1);
    //printf("timetm2 = %ju\n", timetm2);
    sleep(1);
    timet = time(NULL);
    struct tm *timetm = localtime(&timet);
    printf("from tm to timt_t: %ju\n", mktime(timetm)); /* make struct tm to
    time_t */
    
    timet = time(NULL);
    timetm = localtime(&timet);
    strftime(buf,LEN,"%Y-%m-%d %H:%M:%S\n",timetm);
    printf("strftime : %s", buf);

    return 0;
}
