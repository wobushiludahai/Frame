#include <stdio.h>

void bubble_sort(int *buf, int len)
{
    int temp;
    for(int i = 0; i < len-1; i++)
    {
        for(int j = 0; j < len-1-i; j++)
        {
            if(buf[j] > buf[j+1])
            {
                temp = buf[j];
                buf[j] = buf[j+1];
                buf[j+1] = temp;
            }
        }
    }
}

int testbuf[] = {100, 7, 9, -2, 20, -50};

int main(void)
{
    int testlen = sizeof(testbuf)/sizeof(int);
    printf("冒泡排序测试\n");
    printf("排序前: \n");
    for(int i = 0; i < testlen; i++)
    {
        printf("%d ", testbuf[i]);
    }
    printf("\n");
    bubble_sort(testbuf, testlen);
    printf("排序后: \n");
    for(int i = 0; i < testlen; i++)
    {
        printf("%d ", testbuf[i]);
    }
    printf("\n");
}