#include "button.h"

#include "time.h"
#include <string.h>

void button_init(Button_t* btn) {
    if (btn->pin == 0 || btn->port == 0 ) {
        return;
    }

    memset(&btn->_state, 0, sizeof(btn->_state));

    GPIO_InitTypeDef GPIO_InitStructure = {0};
    GPIO_InitStructure.GPIO_Pin = btn->pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_30MHz;
    if (btn->mode == PULL_UP) {
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    } else {
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    }
    GPIO_Init(btn->port, &GPIO_InitStructure); 
}

void button_tick(Button_t* btn) {
    bool pin_level = GPIO_ReadInputDataBit(btn->port, btn->pin);

    bool state;
    if (btn->mode == PULL_UP) {
        state = !pin_level;
    } else {
        state = pin_level;
    }

    if ((state != btn->_state.flag) && (millis() - btn->_state.timer > BTN_DEBOUNCE)) {
        btn->_state.flag = state;
        btn->_state.timer = millis();

        if(state == true)
        {
            btn->_state.press_timer = millis();
            btn->_state.is_held_handled = false;
        } else {
            if ((millis() - btn->_state.press_timer < BTN_HOLD) && (btn->_state.is_held_handled == false)) {
                btn->_state.is_clicked = true;
            }
            btn->_state.is_holding = false;
        }
    }

    if ((state == true) && (millis() - btn->_state.timer > BTN_HOLD)) {
        if (!btn->_state.is_holding) {
            btn->_state.is_held = true;
            btn->_state.is_holding = true;
            btn->_state.is_held_handled = true;
        }
    }
}

bool button_click(Button_t* btn) {
    if (btn->_state.is_clicked == true) {
        btn->_state.is_clicked = false;
        return true;
    }
    return false;
}

bool button_hold(Button_t* btn) {
    if (btn->_state.is_held == true) {
        btn->_state.is_held = false;
        return true;
    }
    return false;
}

bool button_holding(Button_t* btn, uint32_t period) {
    if (btn->_state.is_holding == true) {
        if (millis() - btn->_state.holding_timer >= period) {
            btn->_state.holding_timer = millis();
            return true;
        }
    }
    return false;
}