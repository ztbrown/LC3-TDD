#include <stdlib.h>
#include "sign_extend.h"

uint16_t sign_extend(uint16_t number, int bit_count) {
  if ((number >> (bit_count - 1)) & 1) {
    number |= (0xFFFF << bit_count);
  }
  return number;
}

