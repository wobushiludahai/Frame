/*
 * @Description: a simple timer frame
 * @Author: land sea
 * @Date: 2019-11-08 17:56:13
 * @LastEditTime: 2019-11-09 11:05:07
 * @LastEditors: Please set LastEditors
 */

#ifndef _FRAME_TIMER_H_
#define _FRAME_TIMER_H_

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct timer_t
{
    uint32_t timeout;
    uint64_t timegoal;
    void     (*timeout_handle)(void);
    uint32_t cycletimes;
    TIMER    *next;
}TIMER;

enum timer_state_code
{
    TIMER_STATECODE_ZERO = 0,
    TIMER_STATECODE_SET_OK,             //set success
    TIMER_STATECODE_NONE_EXIST,         //timer does not exist
    TIMER_STATECODE_DELETE_OK,          //delete success
};

/**
 * @description: initialize timer param
 * @param timer: timer struct
 * @param timeout_handle: timeout handle function
 * @param timeout: time value
 * @param cycletimes: time times
 * @return: None
 */
void timer_init(TIMER *timer, void (* timeout_handle)(), uint32_t timeout, uint32_t cycletimes);

/**
 * @description: add timer struct into the loop list
 * @param timer:timer struct
 * @return: None
 */
void timer_add(TIMER *timer);

/**
 * @description: set time times
 * @param time:timer struct
 * @param cycletimes:time tines
 * @return: timer state code
 */
int timer_setcycletimes(TIMER *timer, uint32_t cycletimes);

/**
 * @description: stop one timer in the loop list
 * @param timer:timer struct
 * @return: None
 */
void timer_stop(TIMER *timer);

/**
 * @description: remove onr timer fron the loop list
 * @param timer:timer struct
 * @return: timer state code
 */
int timer_remove(TIMER *timer);

/**
 * @description: main loop, check the timer list
 * @param None 
 * @return: None
 */
void timer_loop(void);

/**
 * @description: use uint64_t, when tick is 1ms, its Inversion stage ≈584942417 years
 * @param None 
 * @return: None
 */
void timer_tick(void);


#ifdef __cplusplus
}
#endif

#endif
