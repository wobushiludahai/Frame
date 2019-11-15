/*
 * @Description: a simple button frame V 1.0
 * @Author: land sea
 * @Date: 2019-11-13 15:46:06
 * @LastEditTime: 2019-11-15 09:40:31
 * @LastEditors: Please set LastEditors
 */

#include "button.h"

#define EVENT_CB(event) \
    do{\
        if(button->cb[event]) button->cb[event]((BUTTON *)button);   \
    }while(0)

static BUTTON *button_handle = NULL;


void button_init(BUTTON *button, uint8_t (*get_level)(), uint8_t level)
{
    memset(button, 0, sizeof(BUTTON));
    button->button_event = BUTTON_EVENT_NONE;
    button->get_button_level = get_level;
    button->curlevel = button->get_button_level();
    button->prelevel = level;
}

void 

