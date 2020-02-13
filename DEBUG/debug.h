#ifndef __DEBUG_H__
#define __DEBUG_H__

#define ERR_LEVEL       3
#define WARN_LEVEL      2
#define DEBUG_LEVEL     1
/*
    PRINT_LEVEL setting:
    0: print off
    1: debug-level messages
    2: warning conditions
    3: err_log
*/
#define PRINT_LEVEL     3

#define ERR(...)                    \
do{                                 \
    if(PRINT_LEVEL >= ERR_LEVEL)    \
    {                               \
        printf(__VA_ARGS__);        \
    }                               \
}while(0)

#define WARN(...)                    \
do{                                 \
    if(PRINT_LEVEL >= WARN_LEVEL)    \
    {                               \
        printf(__VA_ARGS__);        \
    }                               \
}while(0)

#define DEBUG(...)                    \
do{                                 \
    if(PRINT_LEVEL >= DEBUG_LEVEL)    \
    {                               \
        printf(__VA_ARGS__);        \
    }                               \
}while(0)

#endif