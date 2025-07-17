#include "gyro.h"

static byte sda_pin = 0;
static byte scl_pin = 0;

void init_gyro(byte sda, byte scl)
{   
    sda_pin = sda;
    scl_pin = scl;
}