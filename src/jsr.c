#include <stdlib.h>

#include "jsr.h"
#include "vm.h"
#include "sign_extend.h"

void jsr(uint16_t instr) {
  reg[R_R7] = reg[R_PC];
  if (instr >> 11 & 0x1) {
    reg[R_PC] += sign_extend(instr & 0x7FF, 11);
  }
  else {
    reg[R_PC] = reg[instr >> 6 & 0x7]; 
  }
}

