/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2024/01/01
 * Description        : Main program body.
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for 
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

#include "debug.h"
#include "time.h"
#include "button.h"

Button_t btn1;
Button_t btn2;
Button_t btn3;

int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    SystemCoreClockUpdate();
    Delay_Init();
    SDI_Printf_Enable();

    printf("SystemClk:%d\r\n",SystemCoreClock);
    printf( "ChipID:%08x\r\n", DBGMCU_GetCHIPID() );

    RCC_PB2PeriphClockCmd(RCC_PB2Periph_GPIOA | RCC_PB2Periph_GPIOB | RCC_PB2Periph_GPIOC | RCC_PB2Periph_GPIOD, ENABLE);
    systick_init();
    button_init(&btn1, GPIOD, GPIO_Pin_7);
    button_init(&btn2, GPIOD, GPIO_Pin_5);
    button_init(&btn3, GPIOB, GPIO_Pin_5);

    while(1)
    {
        button_tick(&btn1);
        button_tick(&btn2);
        button_tick(&btn3);

        if (button_click(&btn1)) {
            printf("Btn1 clicked!\n\r");
        } 
        // else if (button_hold(&btn1)) {
        //     printf("Btn1 held!\n\r");
        // } 
        else if (button_holding(&btn1, 200)) {
            printf("Btn1 holding!\n\r");
        }

        if (button_click(&btn2)) {
            printf("Btn2 clicked!\n\r");
        } 
        else if (button_hold(&btn2)) {
            printf("Btn2 held!\n\r");
        } 
        // else if (button_holding(&btn2)) {
        //     printf("Btn2 holding!\n\r");
        // }

        if (button_click(&btn3)) {
            printf("Btn3 clicked!\n\r");
        } 
        else if (button_hold(&btn3)) {
            printf("Btn3 held!\n\r");
        } 
        // else if (button_holding(&btn3)) {
        //     printf("Btn3 holding!\n\r");
        // }
    }
}
