#include <stdlib.h>

#include "and.h"

#include "update_flags.h"
#include "sign_extend.h"
#include "vm.h"

void and(uint16_t instr) {
  uint16_t dr = instr >> 9 & 0x7;
  uint16_t sr1 = instr >> 6 & 0x7;
  if (instr >> 5 & 0x1) {
    uint16_t imm5 = sign_extend(instr & 0x1F, 5); 
    reg[dr] = reg[sr1] & imm5;
  }
  else {
    uint16_t sr2 = instr & 0x7;
    reg[dr] = reg[sr1] & reg[sr2];
  }
  update_flags(dr);
}

