#include <stdio.h>

void select_sort(int *buf, int len)
{
    for(int i = 0; i < len; i++)
    {
        int key = i;
        for(int j = i+1; j < len; j++)
        {
            if(buf[j] < buf[key])
            {
                key = j;
            }
        }

        if(key != i)
        {
            int temp = buf[i];
            buf[i] = buf[key];
            buf[key] = temp;
        }
    }
}

int testbuf[] = {100, 7, 9, -2, 20, -50};

int main(void)
{
    int testlen = sizeof(testbuf)/sizeof(int);
    printf("选择排序测试\n");
    printf("排序前: \n");
    for(int i = 0; i < testlen; i++)
    {
        printf("%d ", testbuf[i]);
    }
    printf("\n");
    select_sort(testbuf, testlen);
    printf("排序后: \n");
    for(int i = 0; i < testlen; i++)
    {
        printf("%d ", testbuf[i]);
    }
    printf("\n");
}