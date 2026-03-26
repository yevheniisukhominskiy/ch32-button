#ifndef BUTTON_H
#define BUTTON_H

#include "ch32v00X.h"
#include "stdint.h"
#include "stdbool.h"

#define BTN_DEBOUNCE 30
#define BTN_HOLD 1000
#define BTN_STEP_HOLDING 1000

typedef enum {
    PULL_UP,
    PULL_DOWN
} Mode_t;

typedef struct {
    GPIO_TypeDef* port;
    uint16_t pin;
    Mode_t mode;

    struct {
        uint32_t timer;
        uint32_t press_timer;
        uint32_t holding_timer;
        bool flag;
        bool is_held_handled;
        bool is_clicked;
        bool is_held;
        bool is_holding; 
    } _state;
} Button_t;

void button_init(Button_t* btn);
void button_tick(Button_t* btn);

bool button_click(Button_t* btn);
bool button_hold(Button_t* btn);
bool button_holding(Button_t* btn, uint32_t period);

#endif