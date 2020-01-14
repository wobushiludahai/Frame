/*
 * @Description: 杭电OJ 2044
 * @Author: landsea
 * @Date: 2020-01-14 15:35:04
 * @LastEditTime: 2020-01-14 15:39:46
 * @LastEditors: Please set LastEditors
 */
#include <stdio.h>

int f[55];
int n;
int a, b;

int main()
{
    f[1] = 1;
    f[2] = 2;
    for(int i = 3; i <= 55; i++)
    {
        f[i] = f[i - 1] + f[i - 2];
    }

    scanf("%d", &n);
    while(n--)
    {
        scanf("%d %d", &a, &b);
        printf("%d\n", f[b-a]);
    }
    return 0;
}
