#include "typedef.h"

#ifndef GYRO_H
#define GYRO_H

typedef struct GyroUpdate {
    int16 accel_x;
    int16 accel_y;
    int16 accel_z;
    int16 gyro_x;
    int16 gyro_y;
    int16 gyro_z;
} GyroUpdate;

void init_gyro(byte sda_pin, byte scl_pin);
byte activate_gyro(void);
byte read_gyro(GyroUpdate* upd);

#endif // GYRO_H