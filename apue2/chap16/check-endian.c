#include <stdio.h>
#include <stdlib.h>

union tmp {
    short i;
    char c[2];
};

int main(void)
{
    union tmp t;
    t.i = 0x0102;

    printf("short = 0x%X\n", t.i);
    printf("char[0] = 0x%X\n", t.c[0]);
    printf("char[1] = 0x%X\n", t.c[1]);
    
    if (t.c[0] == 0x02 && t.c[1] == 0x01)
        printf("little-endian.\n");
    else
        printf("big-endian.\n");
}
