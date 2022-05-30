#include <stdlib.h>

#include "sti.h"
#include "memory.h"
#include "sign_extend.h"
#include "vm.h"

void sti(uint16_t instr) {
  uint16_t pcoffset = sign_extend(instr & 0x1ff, 9);
  mem_write(mem_read(reg[R_PC] + pcoffset), reg[instr >> 9 & 0x7]);
}

