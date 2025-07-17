#include "typedef.h"

#ifndef GPIO_H
#define GPIO_H

typedef enum GPIO_PIN_MODE {
    GPIO_PIN_MODE_OUTPUT,
    GPIO_PIN_MODE_INPUT
} GPIO_PIN_MODE;

void set_pin_mode(byte pin, GPIO_PIN_MODE mode);
void set_pin_high(byte pin);
void set_pin_low(byte pin);

#endif // GPIO_H