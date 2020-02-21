#include <stdio.h>

void insert_sort(int *buf, int len)
{
    int temp;
    for(int i = 1; i < len; i++)
    {
        if(buf[i] < buf[i-1])
        {
            temp = buf[i];
            int j = i -1;
            for(; j >= 0 && buf[j] > temp; j--)
            {
                buf[j+1] = buf[j];
            }
            buf[j+1] = temp;
        }
    }
}

int testbuf[] = {100, 7, 9, -2, 20, -50};

int main(void)
{
    int testlen = sizeof(testbuf)/sizeof(int);
    printf("插入排序测试\n");
    printf("排序前: \n");
    for(int i = 0; i < testlen; i++)
    {
        printf("%d ", testbuf[i]);
    }
    printf("\n");
    insert_sort(testbuf, testlen);
    printf("排序后: \n");
    for(int i = 0; i < testlen; i++)
    {
        printf("%d ", testbuf[i]);
    }
    printf("\n");
}