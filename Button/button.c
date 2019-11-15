/*
 * @Description: a simple button frame V 1.0
 * @Author: land sea
 * @Date: 2019-11-13 15:46:06
 * @LastEditTime: 2019-11-15 10:09:40
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
    button->curlevel = button->get_button_level();
    button->prelevel = level;
    button->next = NULL;
}

void button_attch(BUTTON *button, BUTTON_EVENT event, btncallback cb)
{
    button->cb[event] = cb;
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

