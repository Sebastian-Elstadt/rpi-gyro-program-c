#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>

#include "include/config.h"
#include "include/gyro.h"
#include "include/i2c.h"
#include "include/typedef.h"

void map_peripherals_vmem(void);

volatile uint* peripheral_vmem;
volatile uint* gpfsel_registers;
volatile uint* gpset_registers;
volatile uint* gpclr_registers;

int main(void)
{
    // init
    if (open_config() != 0)
        return 1;

    // map_peripherals_vmem();
    init_gyro(read_config_byte("GYRO_SDA_PIN"), read_config_byte("GYRO_SCL_PIN"));

    close_config();

    // prog loop
    if (open_i2c() != 0)
        return 1;

    activate_gyro();

    while (1) {
        GyroUpdate upd = { 0 };
        if (read_gyro(&upd) != 0) break;

        printf("-- gyro update --\n");
        printf("accel: x=%d, y=%d, z=%d", upd.accel_x, upd.accel_y, upd.accel_z);
        printf("gyro: x=%d, y=%d, z=%d", upd.gyro_x, upd.gyro_y, upd.gyro_z);
        printf("\n");

        sleep(1);
    }

    close_i2c();

    return 0;
}

void map_peripherals_vmem(void)
{
    int mem_fd = open("/dev/mem", O_RDWR | O_SYNC); // read+write permission. perform synchronously.
    void* vmem_map = mmap(
        NULL, // let kernel decide where to put in virtual memory.
        4096, // num of bytes.
        PROT_READ | PROT_WRITE, // allow read + write.
        MAP_SHARED, // share virtual state with physical.
        mem_fd, // file descriptor to access physical memory.
        PERIPHERAL_BASE // starting physical address.
    );
    close(mem_fd);
    peripheral_vmem = (volatile uint*)vmem_map;

    gpfsel_registers = peripheral_vmem + GPFSEL_REGISTERS_OFFSET;
    gpset_registers = gpfsel_registers + GPSET_REGISTERS_OFFSET;
    gpclr_registers = gpfsel_registers + GPCLR_REGISTERS_OFFSET;
}