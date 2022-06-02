#include <stdlib.h>

#include "load.h"
#include "vm.h"
#include "memory.h"
#include "sign_extend.h"
#include "update_flags.h"

void load(uint16_t instr) {
  int dr = instr >> 9 & 0x7;
  uint16_t pcoffset = sign_extend(instr & 0x1FF, 9);
  reg[dr] = mem_read(reg[R_PC] + pcoffset);
  update_flags(dr);
}
