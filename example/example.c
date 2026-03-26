#include "debug.h"
#include "time.h"
#include "button.h"

Button_t btn1 = {
    .port = GPIOD,
    .pin = GPIO_Pin_7,
    .mode = PULL_UP,
};

Button_t btn2 = {
    .port = GPIOD,
    .pin = GPIO_Pin_5,
    .mode = PULL_UP,
};

Button_t btn3 = {
    .port = GPIOB,
    .pin = GPIO_Pin_5,
    .mode = PULL_DOWN,
};

int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    SystemCoreClockUpdate();
    Delay_Init();
    SDI_Printf_Enable();

    printf("SystemClk:%d\r\n",SystemCoreClock);
    printf("ChipID:%08x\r\n", DBGMCU_GetCHIPID());

    RCC_PB2PeriphClockCmd(RCC_PB2Periph_GPIOA | RCC_PB2Periph_GPIOB | RCC_PB2Periph_GPIOC | RCC_PB2Periph_GPIOD, ENABLE);
    systick_init();
    
    button_init(&btn1);
    button_init(&btn2);
    button_init(&btn3);

    while(1)
    {
        button_tick(&btn1);
        button_tick(&btn2);
        button_tick(&btn3);

        if (button_click(&btn1)) {
            printf("Btn1 clicked!\n\r");
        } 
        else if (button_holding(&btn1, 200)) {
            printf("Btn1 holding!\n\r");
        }

        if (button_click(&btn2)) {
            printf("Btn2 clicked!\n\r");
        } 
        else if (button_hold(&btn2)) {
            printf("Btn2 held!\n\r");
        } 

        if (button_click(&btn3)) {
            printf("Btn3 clicked!\n\r");
        } 
        else if (button_hold(&btn3)) {
            printf("Btn3 held!\n\r");
        } 
    }
}
