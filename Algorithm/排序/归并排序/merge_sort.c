#include <stdio.h>

void MemeryArray(int a[], int n, int b[], int m, int c[])
{
 int i, j, k;

 i = j = k = 0;
 while (i < n && j < m)
 {
     if (a[i] < b[j])
         c[k++] = a[i++];
     else
         c[k++] = b[j++]; 
 }

 while (i < n)
     c[k++] = a[i++];

 while (j < m)
     c[k++] = b[j++];
}

void merge(int *a, int n, int *b, int m, int *c)
{
    int i, j , k;

    i = j = k = 0;
    while (i < n && j < m)
    {
        if(a[i] < b[j])
        {
            c[k++] = a[i++];
        }
        else
        {
            c[k++] = b[j++];
        }
    }

    while(i < n)
    {
        c[k++] = a[i++];
    }

    while(j < m)
    {
        c[k++] = b[j++];
    }
}

void merge_sort(int *buf, int len)
{

}

int testbuf[] = {100, 7, 9, -2, 20, -50};

int main(void)
{
    int testlen = sizeof(testbuf)/sizeof(int);
    printf("归并排序测试\n");
    printf("排序前: \n");
    for(int i = 0; i < testlen; i++)
    {
        printf("%d ", testbuf[i]);
    }
    printf("\n");
    merge_sort(testbuf, testlen);
    printf("排序后: \n");
    for(int i = 0; i < testlen; i++)
    {
        printf("%d ", testbuf[i]);
    }
    printf("\n");
}