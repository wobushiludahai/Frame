/*
 * @Description: a simple button frame  V 1.0
 * @Author: land sea
 * @Date: 2019-11-13 15:46:15
 * @LastEditTime: 2019-11-15 11:44:39
 * @LastEditors: Please set LastEditors
 */
#ifndef _FRAME_BUTTON_H_
#define _FRAME_BUTTON_H_

#include <stdint.h>
#include <stddef.h>

typedef void (*btncallback)(void *);

#define BUTTON_TICK_INTERVAL            5       //tick 时间为5ms
#define BUTTON_TICKS_DEBOUNCE           3       //消抖
#define BUTTON_TICKS_SHORT              60      //单次按键 
#define BUTTON_TICKS_LONG               200     //长按

typedef enum button_event_code
{
    BUTTON_EVENT_PRESS_DOWN = 0,
    BUTTON_EVENT_PRESS_UP,
    BUTTON_EVENT_PRESS_REPEAT,
    BUTTON_EVENT_SINGLE_CLICK,
    BUTTON_EVENT_DOUBLE_CLICK,
    BUTTON_EVENT_LONG_PRESS_START,
    BUTTON_EVENT_LONG_PRESS_HOLD,
    number_of_event,
    BUTTON_EVENT_NONE
}BUTTON_EVENT;

typedef enum button_state_code
{
    BUTTON_STATECODE_ZERO = 0,
    BUTTON_STATECODE_SET_OK,             //set success
    BUTTON_STATECODE_NONE_EXIST,         //button does not exist
    BUTTON_STATECODE_REMOVE_OK,          //remove success
}BUTTON_STATE_CODE;

typedef struct
{
    uint8_t     (*get_button_level)(void);
    uint8_t     button_level;                   //当前电平
    uint8_t     trigger_level;                  //触发电平
    uint16_t    timer_count;
    uint8_t     button_timescount;              //次数统计
    uint8_t     button_state;                   //状态
    uint8_t     debounce_cnt;                   //消抖
    uint8_t     button_event;
    btncallback cb[number_of_event];            //回调函数列表
    BUTTON      *next;
}BUTTON;


#ifdef __cplusplus  
extern "C" {  
#endif  

void button_init(BUTTON *button, uint8_t (*get_level)(), uint8_t level);
int button_attch(BUTTON *button, BUTTON_EVENT event, btncallback cb);
void button_add(BUTTON *button);
int button_remove(BUTTON *button);
void button_handler(BUTTON *button);
void button_loop_cycle_call(void);

#ifdef __cplusplus
} 
#endif

#endif
