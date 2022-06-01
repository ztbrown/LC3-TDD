#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>

#define MEMORY_MAX (1 << 16)

uint16_t mem_read(uint16_t address);
void mem_write(uint16_t address, uint16_t value);

#endif // MEMORY_H


