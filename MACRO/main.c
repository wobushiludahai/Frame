#include <stdio.h>
#include "macro1.h"
#include "macro2.h"

typedef struct
{
    int val;
    int *pvar;
}num_t;

int test_num;

const num_t testtab[] = 
{
    {TEST_NUM_PRINT_VAL, &test_num},
};

int main(void)
{
    //表格变量和宏定义值对应
    *testtab[0].pvar = testtab[0].val;

    //验证
    printf("macro value: %d", TEST_NUM_PRINT);
}