#include "button.h"

#include "time.h"

void button_init(Button_t* btn, GPIO_TypeDef* port, uint16_t pin) {
    btn->port = port;
    btn->pin = pin;
    btn->_flag = false;
    btn->_is_held_handled = false;
    btn->_is_clicked = false;
    btn->_is_held = false;
    btn->_is_holding = false;

    GPIO_InitTypeDef GPIO_InitStructure = {0};
    GPIO_InitStructure.GPIO_Pin = pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_30MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(port, &GPIO_InitStructure);
    
}

void button_tick(Button_t* btn) {
    bool state = !GPIO_ReadInputDataBit(btn->port, btn->pin);

    if ((state != btn->_flag) && (millis() - btn->_timer > BTN_DEBOUNCE)) {
        btn->_flag = state;
        btn->_timer = millis();

        if(state == true)
        {
            btn->_press_timer = millis();
            btn->_is_held_handled = false;
        } else {
            if ((millis() - btn->_press_timer < BTN_HOLD) && (btn->_is_held_handled == false)) {
                btn->_is_clicked = true;
            }
            btn->_is_holding = false;
        }
    }

    if ((state == true) && (millis() - btn->_timer > BTN_HOLD)) {
        if (!btn->_is_holding) {
            btn->_is_held = true;
            btn->_is_holding = true;
            btn->_is_held_handled = true;
        }
    }
}

bool button_click(Button_t* btn) {
    if (btn->_is_clicked == true) {
        btn->_is_clicked = false;
        return true;
    }
    return false;
}

bool button_hold(Button_t* btn) {
    if (btn->_is_held == true) {
        btn->_is_held = false;
        return true;
    }
    return false;
}

bool button_holding(Button_t* btn, uint32_t period) {
    if (btn->_is_holding == true) {
        if (millis() - btn->_holding_timer >= period) {
            btn->_holding_timer = millis();
            return true;
        }
    }
    return false;
}