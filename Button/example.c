/*
 * @Description: a simple button frame example
 * @Author: land sea
 * @Date: 2019-11-13 17:37:43
 * @LastEditTime: 2019-11-15 11:44:33
 * @LastEditors: Please set LastEditors
 */

#include "button.h"

BUTTON buttonexample;

uint8_t get_buttonexample_level(void)
{
    return HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9);
}

void buttonexample_pressdown_handler(BUTTON* button)
{
    printf("button press up!");
}

int main(void)
{
    board_init();     //硬件初始化

    button_init(&buttonexample, get_buttonexample_level, 0);

    //需要为每个event添加对应的callback函数
    button_attch(&buttonexample, BUTTON_EVENT_PRESS_UP, buttonexample_pressdown_handler);

    button_add(&buttonexample);

    //make caution
    //you need to make a timer invoking button_loop_cycle_call()
    //inerval 5ms recommended

    while(1)
    {
    }
}