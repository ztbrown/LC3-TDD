#include <stdlib.h>

#include "load.h"
#include "vm.h"
#include "sign_extend.h"
#include "update_flags.h"

void load(uint16_t instr) {
  int dr = instr >> 9 & 0x7;
  reg[dr] = sign_extend(instr & 0x1FF, 9);
  update_flags(dr);
}
