#include <stdlib.h>
#include "update_flags.h"
#include "vm.h"

void update_flags(uint16_t r) {
  if (reg[r] == 0) {
    reg[R_COND] = FL_ZRO;
  } 
  else if (reg[r] >> 15) {
    reg[R_COND] = FL_NEG;
  }
  else {
    reg[R_COND] = FL_POS;
  } 
}
