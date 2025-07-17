#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "i2c.h"

int i2c_fd;

byte open_i2c(void)
{
    if ((i2c_fd = open("/dev/i2c-1", O_RDWR)) < 0) {
        printf("error: failed to open i2c device.\n");
        return 1;
    }

    printf("info: i2c device opened.\n");
    return 0;
}

byte set_i2c_slave(byte addr)
{
    if (ioctl(i2c_fd, I2C_SLAVE, addr) < 0) {
        printf("error: failed to set i2c slave addr: %hhx\n", addr);
        return 1;
    }

    printf("info: i2c slave addr set to: %hhx\n", addr);
    return 0;
}

byte write_i2c(byte data[], byte len)
{
    if (write(i2c_fd, data, len) != len) {
        printf("error: i2c write failed.\n");
        return 1;
    }

    return 0;
}

byte read_i2c(byte data[], byte len)
{
    if (read(i2c_fd, data, len) != len) {
        printf("error: i2c read failed.\n");
        return 1;
    }

    return 0;
}

void close_i2c(void)
{
    printf("info: closing i2c device.\n");
    close(i2c_fd);
}