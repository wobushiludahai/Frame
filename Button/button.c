/*
 * @Description: a simple button frame V 1.0
 * @Author: land sea
 * @Date: 2019-11-13 15:46:06
 * @LastEditTime: 2019-11-15 11:26:22
 * @LastEditors: Please set LastEditors
 */

#include "button.h"

#define EVENT_CB(event) \
    do{\
        if(button->cb[event]) button->cb[event]((BUTTON *)button);   \
    }while(0)

static BUTTON *button_handle_head = NULL;


void button_init(BUTTON *button, uint8_t (*get_level)(), uint8_t level)
{
    memset(button, 0, sizeof(BUTTON));
    button->button_event = BUTTON_EVENT_NONE;
    button->get_button_level = get_level;
    button->button_level = button->get_button_level();
    button->trigger_level = level;
    button->timer_count = 0;
    button->next = NULL;
}

int button_attch(BUTTON *button, BUTTON_EVENT event, btncallback cb)
{
    if(button == NULL)
    {
        return BUTTON_STATECODE_NONE_EXIST;
    }
    button->cb[event] = cb;
    return BUTTON_STATECODE_SET_OK;
}

void button_add(BUTTON *button)
{
    BUTTON *ptbutton;
    
    ptbutton = button_handle_head;

    while(ptbutton)
    {
        if(ptbutton == button){     //已经存在
            return;
        }
        ptbutton = ptbutton->next;
    }
    button->next = button_handle_head;
    button_handle_head = button;
}

int button_remove(BUTTON *button)
{
    BUTTON *ptbuttoncur, *ptbuttonpre = NULL;

    ptbuttoncur = button_handle_head;

    while(ptbuttoncur)
    {
        if(ptbuttoncur == button)
        {
            if(ptbuttonpre) ptbuttonpre->next = ptbuttoncur->next;
            else button_handle_head = ptbuttoncur->next;        //the button is button list head
            return BUTTON_STATECODE_REMOVE_OK;
        }
        ptbuttonpre = ptbuttoncur;
        ptbuttoncur = ptbuttoncur->next;
    }

    return BUTTON_STATECODE_NONE_EXIST;                     //想移除的button不存在
}

void button_handler(BUTTON *button)
{
    uint8_t temp_level = button->get_button_level();

    if(button->button_state > 0) button->timer_count++;

    if(temp_level != button->button_level)
    {
        if(++(button->debounce_cnt) >= BUTTON_TICKS_DEBOUNCE)   //防抖
        {
            button->button_level = temp_level;
            button->debounce_cnt = 0;
        }
        else
        {
            button->debounce_cnt = 0;
        }
    }

    switch(button->button_state)
    {
        case 0:
            {
                if(button->button_level == button->trigger_level)   //按键按下
                {
                    button->button_event = BUTTON_EVENT_PRESS_DOWN;
                    EVENT_CB(BUTTON_EVENT_PRESS_DOWN);              //调用回调函数
                    button->timer_count = 0;
                    button->button_timescount = 1;
                    button->button_state = 1;                       //状态切换
                }
                else
                {
                    button->button_event = BUTTON_EVENT_NONE;
                }
            }
            break;

        case 1:
            {
                if(button->button_level != button->trigger_level)   //按键被释放
                {
                    button->button_event = BUTTON_EVENT_PRESS_UP;
                    EVENT_CB(BUTTON_EVENT_PRESS_UP);
                    button->timer_count = 0;
                    button->button_state = 2;
                }
                else if(button->timer_count > BUTTON_TICKS_LONG)    //长按
                {
                    button->button_event = BUTTON_EVENT_LONG_PRESS_START;
                    EVENT_CB(BUTTON_EVENT_LONG_PRESS_START);
                    button->button_state = 5;       
                }
            }
            break;

        case 2:
            {
                if(button->button_level == button->trigger_level)   //按键再次被按下
                {
                    button->button_event = BUTTON_EVENT_PRESS_DOWN;
                    EVENT_CB(BUTTON_EVENT_PRESS_DOWN);              //调用回调函数
                    button->button_timescount++;
                    if(button->button_timescount == 2)              //第二次被按下（双击）
                    {
                        EVENT_CB(BUTTON_EVENT_DOUBLE_CLICK);
                    }
                    EVENT_CB(BUTTON_EVENT_PRESS_REPEAT);            //当被多次按下
                    button->timer_count = 0;
                    button->button_state = 3;
                }
                else if(button->timer_count > BUTTON_TICKS_SHORT)   //按键未被多次按下
                {
                    if(button->button_timescount == 1)
                    {
                        button->button_event = BUTTON_EVENT_SINGLE_CLICK;   
                        EVENT_CB(BUTTON_EVENT_SINGLE_CLICK);              //单击回调函数
                    }
                    else if (button->button_timescount == 2)
                    {
                        button->button_event = BUTTON_EVENT_DOUBLE_CLICK;
                        EVENT_CB(BUTTON_EVENT_DOUBLE_CLICK);              //双击回调函数
                    }
                    button->button_state = 0;                       //回到初始状态
                }
            }
            break;

        case 3:
            {
                if(button->button_level != button->trigger_level)   //按键再次被释放
                {
                    button->button_event = BUTTON_EVENT_PRESS_UP;
                    EVENT_CB(BUTTON_EVENT_PRESS_UP);
                    if(button->timer_count < BUTTON_TICKS_SHORT)
                    {
                        button->timer_count = 0;
                        button->button_state = 2;       //再次进入是否再次被按下逻辑
                    }
                    else
                    {
                        button->button_state = 0;       //回到初始状态
                    }
                }
            }
            break;

        case 5: 
            {
                if(button->button_level == button->trigger_level)   //长按保持
                {
                    button->button_event = BUTTON_EVENT_LONG_PRESS_HOLD;
                    EVENT_CB(BUTTON_EVENT_LONG_PRESS_HOLD);
                }
                else                                                //长按被释放
                {
                    button->button_event = BUTTON_EVENT_PRESS_UP;
                    EVENT_CB(BUTTON_EVENT_PRESS_UP);
                    button->button_state = 0;                       //回到初始状态
                }
            }
            break;

        default:
            break;
    }
}

void button_loop_cycle_call(void)
{
    BUTTON *ptbutton;

    ptbutton = button_handle_head;

    while(ptbutton)
    {
        button_handler(ptbutton);
        ptbutton = ptbutton->next;
    }
    
}

