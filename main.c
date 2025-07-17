#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>

#include "include/config.h"
#include "include/gyro.h"
#include "include/typedef.h"

void init_mem(void);

volatile uint* peripheral_vmem;
volatile uint* gpfsel_registers;
volatile uint* gpset_registers;
volatile uint* gpclr_registers;

int main(void)
{
    open_config();

    init_mem();
    init_gyro(read_config_byte("GYRO_SDA_PIN"), read_config_byte("GYRO_SCL_PIN"));

    close_config();

    return 0;
}

void init_mem(void)
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