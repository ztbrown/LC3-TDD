#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

int main() {
  uint16_t result = 0x7FF & 0x7FF;
  printf("%u\n", (uint16_t)result);
  return 0;
}
