#include <stdlib.h>

#include "conditional_branch.h"
#include "sign_extend.h"
#include "vm.h"

void conditional_branch(uint16_t instr) {
  uint16_t cond_flag = (instr >> 9) & 0x7;
  if (cond_flag & reg[R_COND]) { 
    reg[R_PC] += sign_extend(instr & 0x1FF, 9);
  }
}

