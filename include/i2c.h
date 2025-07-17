#include "typedef.h"

#ifndef I2C_H
#define I2C_H

byte open_i2c(void);
byte set_i2c_slave(byte addr);
byte write_i2c(byte data[], byte len);
byte read_i2c(byte* data, byte len);
void close_i2c(void);

#endif // I2C_H