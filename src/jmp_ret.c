#include <stdlib.h>

#include "jmp_ret.h"
#include "sign_extend.h"
#include "vm.h"

void jmp_ret(uint16_t instr) {
  reg[R_PC] = reg[instr >> 6 & 0x7];
}
