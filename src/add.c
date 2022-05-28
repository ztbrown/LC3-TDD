#include <stdlib.h>

#include "add.h"
#include "sign_extend.h"
#include "update_flags.h"
#include "vm.h"

void add(uint16_t instr) {
  int source = (instr >> 6) & 0x7;
  int destination = (instr >> 9) & 0x7;
  if ((instr >> 5) & 0x1) {
    uint16_t imm5 = sign_extend(instr & 0x1f, 5);
    reg[destination] = reg[source] + imm5;
  }
  else {
    int sr2 = instr & 0x7;
    reg[destination] = reg[source] + reg[sr2];
  }
  update_flags(destination);
}
