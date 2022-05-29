#include "ldi.h"
#include "vm.h"
#include "memory.h"
#include "update_flags.h"

void ldi(uint16_t instr) {
  uint16_t r0 = (instr >> 9) & 0x7;
  uint16_t pcoffset = instr & 0x1FF;
  reg[r0] = mem_read(mem_read(reg[R_PC] + pcoffset));
  update_flags(r0);
}

