#include "config.h"
#include <stdio.h>

static FILE* cfg_file;

byte open_config(void)
{
    cfg_file = fopen("config", 'r');
    if (cfg_file == NULL) { 
        printf("error: failed to open config file.\n");
        return 1;
    }
    
    return 0;
}

void close_config(void)
{
    fclose(cfg_file);
    cfg_file = NULL;
}

byte read_config_byte(const char* property)
{
    byte val = 0;
    fscanf(cfg_file, (*property) + "=%d", &val);
    return val;
}