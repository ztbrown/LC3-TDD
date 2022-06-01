#include <stdlib.h>

#include "memory.h"
#include "sign_extend.h"
#include "update_flags.h"
#include "vm.h"

#include "ldr.h"

void ldr(uint16_t instr) {
  uint16_t dr = instr >> 9 & 0x7;
  reg[dr] = mem_read(reg[(instr >> 6 & 0x7)] + sign_extend(instr & 0x3F, 6));
  update_flags(dr);
}

