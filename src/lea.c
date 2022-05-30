#include <stdlib.h>

#include "lea.h"
#include "vm.h"
#include "update_flags.h"
#include "sign_extend.h"

void lea(uint16_t instr) {
  int dr = instr >> 9 & 0x7;
  reg[dr] = reg[R_PC] + sign_extend(instr & 0x1ff, 9);
  update_flags(dr);
}

