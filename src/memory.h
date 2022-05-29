#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>

uint16_t mem_read(uint16_t address);
void mem_write(uint16_t address, uint16_t value);

#endif // MEMORY_H


