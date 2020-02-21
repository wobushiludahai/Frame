#include <stdio.h>

void shell_sort(int *buf, int len)
{
   int temp = 0;
   int incre = len;

    while(1)
    {
        incre = incre/2;

        for(int k = 0; k < incre; k++)
        {
            for(int i = k+incre; i < len; i+=incre)
            {
                for(int j = i; j > k; j -= incre)
                {
                    if(buf[j] < buf[j-incre])
                    {
                        temp = buf[j - incre];
                        buf[j-incre] = buf[j];
                        buf[j] = temp;
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }

        if(incre == 1)
        {
            break;
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
    shell_sort(testbuf, testlen);
    printf("排序后: \n");
    for(int i = 0; i < testlen; i++)
    {
        printf("%d ", testbuf[i]);
    }
    printf("\n");
}