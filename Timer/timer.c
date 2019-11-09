/*
 * @Description: a simple timer frame
 * @Author: land sea
 * @Date: 2019-11-08 17:56:13
 * @LastEditTime: 2019-11-09 11:05:05
 * @LastEditors: Please set LastEditors
 */

#include "timer.h"

//internal ticks
static uint64_t _timerticks = 0;

static TIMER *timer_list_head = NULL;

void timer_init(TIMER *timer, void (* timeout_handle)(), uint32_t timeout, uint32_t cycletimes)
{
    timer->timeout_handle = timeout_handle;
    timer->timeout = timeout;
    timer->cycletimes = cycletimes;
    timer->next = NULL;
}

void timer_add(TIMER *timer)
{
    TIMER *pttimer;

    pttimer = timer_list_head;
    
    while(pttimer)
    {
        if(pttimer == timer){
            timer->timegoal = _timerticks + timer->timeout;
            return;
        }
        pttimer = pttimer->next;
    }
    timer->next = timer_list_head;
    timer_list_head = timer;
    timer->timegoal = _timerticks + timer->timeout;
}

int timer_setcycletimes(TIMER *timer, uint32_t cycletimes)
{
    TIMER *pttimer;

    pttimer = timer_list_head;

    while(pttimer)
    {
        if(pttimer == timer){
            pttimer->cycletimes = cycletimes;
            return TIMER_STATECODE_SET_OK;
        }
        pttimer = pttimer->next;
    }
    return TIMER_STATECODE_NONE_EXIST;
}

void timer_stop(TIMER *timer)
{
    timer->cycletimes = 0;
}

int timer_remove(TIMER *timer)
{
    TIMER *pttimercur, *pttimerpre = NULL;

    pttimercur = timer_list_head;
    
    while(pttimercur)
    {
        if(pttimercur == timer){
            if(pttimerpre) pttimerpre->next = pttimercur->next;
            else timer_list_head = pttimercur->next;    //the timer need to remove is timerlist head
            return TIMER_STATECODE_DELETE_OK;
        }
        pttimerpre = pttimercur;
        pttimercur = pttimercur->next;
    }
    return TIMER_STATECODE_NONE_EXIST;
}

void timer_loop(void)
{
    TIMER *pttimer;

    pttimer = timer_list_head;

    while(pttimer)
    {
        if((pttimer->cycletimes > 0)&&(_timerticks >= pttimer->timegoal))
        {
            pttimer->timeout_handle();
            if(--pttimer->cycletimes > 0)
            {
                pttimer->timegoal = _timerticks + pttimer->timeout;
            }
        }
        pttimer = pttimer->next;
    }
}

void timer_tick(void)
{
    _timerticks++;
}

