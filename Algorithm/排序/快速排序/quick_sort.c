#include <stdio.h>

void quick_sort(int *buf, int left, int right)
{
    int i, j, temp;
    if(left > right)
    {
        return;
    }

    temp = buf[left];
    i = left;
    j = right;
    while(i != j)
    {
        while(buf[j] >= temp && i < j)
        {
            j--;
        }

        while (buf[i] <= temp && i < j)
        {
            i++;
        }

        if(i != j)
        {
            int k = buf[i];
            buf[i] = buf[j];
            buf[j] = k;
        }
    }

    buf[left] = buf[i];
    buf[i] = temp;

    quick_sort(buf, left, i-1);
    quick_sort(buf, i+1, right);
}

int testbuf[] = {100, 7, 9, -2, 20, -50};

int main(void)
{
    int testlen = sizeof(testbuf)/sizeof(int);
    printf("快速排序测试\n");
    printf("排序前: \n");
    for(int i = 0; i < testlen; i++)
    {
        printf("%d ", testbuf[i]);
    }
    printf("\n");
    quick_sort(testbuf, 0, testlen);
    printf("排序后: \n");
    for(int i = 0; i < testlen; i++)
    {
        printf("%d ", testbuf[i]);
    }
    printf("\n");
}