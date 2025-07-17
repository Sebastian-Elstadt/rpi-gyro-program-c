#include "typedef.h"

#ifndef CONFIG_H
#define CONFIG_H

#define PERIPHERAL_BASE 0x3F000000

#define GPFSEL_REGISTERS_OFFSET 0x200000
#define GPSET_REGISTERS_OFFSET 0x1C // 7 (28 bytes)
#define GPCLR_REGISTERS_OFFSET 0x28 // 10 (40 bytes)

void open_config(void);
void close_config(void);
byte read_config_byte(const char* property);

#endif // CONFIG_H