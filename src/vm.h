#ifndef VM_H
#define VM_H

#include <stdint.h>

enum REGISTERS
{
  R_R0 = 0,
  R_R1,
  R_R2,
  R_R3,
  R_R4,
  R_R5,
  R_R6,
  R_R7,
  R_PC, /* program counter */
  R_COND,
  R_COUNT
};

enum FLAGS
{
  FL_POS = 1 << 0, /* P */
  FL_ZRO = 1 << 1, /* Z */
  FL_NEG = 1 << 2, /* N */
};

extern uint16_t reg[R_COUNT];
extern int running;
extern enum REGISTERS registers;
extern enum FLAGS flags;

#endif // VM_H

