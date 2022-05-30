#include <stdlib.h>

#include "not.h"

#include "vm.h"
#include "update_flags.h"

void not(uint16_t instr) {
  int dr = instr >> 9 & 0x7;
  int sr = instr >> 6 & 0x7;

  reg[dr] = ~reg[sr];
  update_flags(dr);
}

