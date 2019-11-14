/*
 * @Description: a simple button frame  V 1.0
 * @Author: land sea
 * @Date: 2019-11-13 15:46:15
 * @LastEditTime: 2019-11-14 23:14:41
 * @LastEditors: Please set LastEditors
 */
#ifndef _FRAME_BUTTON_H_
#define _FRAME_BUTTON_H_

#include <stdint.h>
#include <stddef.h>


typedef enum button_event_code
{
    BUTTON_EVENT_PRESS_DOWN = 0,
    BUTTON_EVENT_PRESS_UP,
    BUTTON_EVENT_PRESS_DOUBLE,
    BUTTON_EVENT_SINGLE_CLICK,
    BUTTON_EVENT_DOUBLE_CLICK,
    BUTTON_EVENT_LONG_PRESS_START,
    BUTTON_EVENT_LONG_PRESS_HOLD,
    number_of_event,
    BUTTON_EVENT_NONE
}BUTTON_EVENT;


typedef struct
{
    
}BUTTON;


#ifdef __cplusplus  
extern "C" {  
#endif  


#ifdef __cplusplus
} 
#endif

#endif
