#include <stdlib.h>
#include <stdio.h>

#include "trap.h"
#include "memory.h"
#include "prompt.h"
#include "update_flags.h"
#include "vm.h"

enum
{
  TRAP_GETC = 0x20,  /* get character from keyboard, not echoed onto the terminal */
  TRAP_OUT = 0x21,   /* output a character */
  TRAP_PUTS = 0x22,  /* output a word string */
  TRAP_IN = 0x23,    /* get character from keyboard, echoed onto the terminal */
  TRAP_PUTSP = 0x24, /* output a byte string */
  TRAP_HALT = 0x25   /* halt the program */
};

void trap(uint16_t instr) {
  switch(instr & 0xFF)
  {
    case TRAP_GETC:
      {
        reg[R_R0]=(uint16_t)getchar();
        break;
      }
    case TRAP_OUT:
      {
        putchar((uint16_t)reg[R_R0]);
        fflush(stdout);
        break;
      }
    case TRAP_PUTS: 
      {
        uint16_t c = reg[R_R0];

        while(mem_read(c)) {
          putchar((char)mem_read(c));
          ++c;
        } 
        fflush(stdout);
        break;
      }
    case TRAP_IN:
      {
        prompt("Enter a character: ");
        reg[R_R0]=(uint16_t)getchar();
        putchar((uint16_t)reg[R_R0]);
        fflush(stdout);
        update_flags(R_R0);
        break;
      }
    case TRAP_PUTSP:
      {
        uint16_t c = reg[R_R0];

        while(mem_read(c)) {
          putchar((char)mem_read(c & 0xFF));
          char ch2 = (char)mem_read(c >> 8);
          if (ch2) putchar(ch2);
          ++c;
        } 
        fflush(stdout);
        break;
      }
    case TRAP_HALT:
      {
        prompt("HALT");
        running=0;
        fflush(stdout);
      }
  }
}

