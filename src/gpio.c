#include "gpio.h"

extern volatile uint* gpfsel_registers;
extern volatile uint* gpfsel_registers;
extern volatile uint* gpclr_registers;

void set_pin_mode(byte pin, GPIO_PIN_MODE mode)
{
    // each pin has 3 bits per register to control its mode.
    int regIdx = pin / 10;
    int bitOffset = (pin % 10) * 3;

    volatile uint* reg = &gpfsel_registers[regIdx];
    *reg &= ~(7 << bitOffset);

    if (mode == GPIO_PIN_MODE_OUTPUT) {
        *reg |= (1 << bitOffset);
    }
}

void set_pin_high(byte pin)
{
    // each bit corrosponds to a pin.
    int regIdx = pin / 32;
    gpfsel_registers[regIdx] = 1 << pin;
}

void set_pin_low(byte pin)
{
    // each bit corrosponds to a pin.
    int regIdx = pin / 32;
    gpclr_registers[regIdx] = 1 << pin;
}