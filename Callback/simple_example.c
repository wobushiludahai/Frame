/*
 * @Description: 回调函数C语言版本
 * @Author: 陆海
 * @Date: 2019-12-17 17:55:33
 * @LastEditTime: 2019-12-17 18:01:00
 * @LastEditors: Please set LastEditors
 */
#include <stdio.h>

typedef void (*callbackexample_t) (void);

void callback1(void)
{
    printf("callback test1\n");
}

void callback2(void)
{
    printf("callback test2\n");
}

int main(void)
{
    callbackexample_t callback;

    callback = callback1;

    callback();

    callback = callback2;

    callback();
    
    return 0;
}