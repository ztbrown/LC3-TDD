#include <stdlib.h>

#include "store.h"

#include "memory.h"
#include "sign_extend.h"
#include "vm.h"

void store(uint16_t instr) {
  uint16_t addr = reg[R_PC] + sign_extend(instr & 0x1ff, 9);
  mem_write(addr, reg[instr >> 9 & 0x7]);
}

