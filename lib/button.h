#ifndef BUTTON_H
#define BUTTON_H

#include "ch32v00X.h"
#include "stdint.h"
#include "stdbool.h"

#define BTN_DEBOUNCE 30
#define BTN_HOLD 1000
#define BTN_STEP_HOLDING 1000

typedef struct {
    GPIO_TypeDef* port;
    uint16_t pin;

    uint32_t _timer;
    uint32_t _press_timer;
    uint32_t _holding_timer;

    bool _flag;
    bool _is_held_handled;

    bool _is_clicked;
    bool _is_held;
    bool _is_holding; 
} Button_t;

void button_init(Button_t* btn, GPIO_TypeDef* port, uint16_t pin);
void button_tick(Button_t* btn);

bool button_click(Button_t* btn);
bool button_hold(Button_t* btn);
bool button_holding(Button_t* btn, uint32_t period);

#endif