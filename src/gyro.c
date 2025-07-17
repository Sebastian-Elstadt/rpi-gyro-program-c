#include <stdio.h>

#include "gyro.h"
#include "i2c.h"

#define GY521_I2C_ADDR 0x68
#define PWR_MGMT_1 0x6B
#define ACCEL_XOUT_H 0x3B

static byte sda_pin = 0;
static byte scl_pin = 0;

void init_gyro(byte sda, byte scl)
{
    sda_pin = sda;
    scl_pin = scl;
}

byte activate_gyro(void)
{
    printf("info: activating gyro.\n");

    if (set_i2c_slave(GY521_I2C_ADDR) != 0) {
        printf("error: failed to set gyro as i2c slave address.\n");
        return 1;
    }

    if (write_i2c((byte[]) { PWR_MGMT_1, 0x00 }, 2) != 0) { // wake gyro
        printf("error: failed to wake gyro.\n");
        return 1;
    }

    if (write_i2c((byte[]) { ACCEL_XOUT_H }, 1) != 0) {
        printf("error: failed to set gyro register.\n");
        return 1;
    }

    return 0;
}

byte read_gyro(GyroUpdate* upd)
{
    byte buffer[14] = { 0 };
    if (read_i2c(buffer, 14) != 0) {
        printf("error: failed to read from gyro.\n");
        return 1;
    }

    upd->accel_x = (buffer[0] << 8) | buffer[1];
    upd->accel_y = (buffer[2] << 8) | buffer[3];
    upd->accel_z = (buffer[4] << 8) | buffer[5];
    upd->gyro_x = (buffer[8] << 8) | buffer[9];
    upd->gyro_y = (buffer[10] << 8) | buffer[11];
    upd->gyro_z = (buffer[12] << 8) | buffer[13];

    return 0;
}
