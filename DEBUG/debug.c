#include <stdio.h>
#include "debug.h"

int main(void)
{
    ERR("error test\n");
    WARN("warn test\n");
    DEBUG("debug error\n");

    return 0;
}