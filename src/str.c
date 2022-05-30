#include <stdlib.h>

#include "str.h"
#include "memory.h"
#include "sign_extend.h"
#include "vm.h"

void str(uint16_t instr) {
  int baseR = instr >> 6 & 0x7;
  int sr = instr >> 9 & 0x7;

  uint16_t offset = sign_extend(instr & 0x3F, 6);

  mem_write(offset + reg[baseR], reg[sr]);
}

