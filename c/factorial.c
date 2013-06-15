#include <stdio.h>

#define MAX_FACTOR      100
#define MAX_ARRAY_LEN   100

int array[MAX_ARRAY_LEN];

int factorial(int x)
{
    int i = 0;
    int j = 0;
    int jj = 0;
    int n1 = 1;  //结果的位数
    int n2 = 1;
    int tmp = 0;
    memset(array, 0x00, sizeof(array));
    array[0] = 1;

    // i为乘数
    for (i = 2; i <= x; i++) {
    	// 每位与乘数做运算
        for (j = 0; j < n1; j++) {
        	array[j] = array[j]*i;
        }

        // 每位乘运算后，进行补位
        for (j = 0, jj = 0; j < n1; j++) {
        	jj = j;
            while (array[jj] / 10) {
                tmp = array[jj] / 10;	// 保存进位数
                array[jj] = array[jj] % 10;

                jj++;
                array[jj] += tmp;		//将进位加到高位上

                if (jj >= n1) {
                    n2 = jj + 1;
                }
            }
        }
        // 运算之后数字的位数
        if (n1 != n2) {
        	n1 = n2;
        }
    }

    for (i = n1-1; i >= 0; i--) {
        printf("%d", array[i]);
    }

}

int main(void)
{
    factorial(100);
}

