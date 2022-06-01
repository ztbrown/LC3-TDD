#include <stdlib.h>

#include "memory.h"

uint16_t memory[MEMORY_MAX]; 

uint16_t mem_read(uint16_t address) {
  return memory[address];
}

void mem_write(uint16_t address, uint16_t value) {
  memory[address] = value;
}

