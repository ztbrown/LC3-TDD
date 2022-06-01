#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <signal.h>

#include <unistd.h>
#include <fcntl.h>

#include <sys/time.h>
#include <sys/types.h>
#include <sys/termios.h>
#include <sys/mman.h>

#include "vm.h"
#include "memory.h"
#include "add.h"
#include "and.h"
#include "conditional_branch.h"
#include "image.h"
#include "jmp_ret.h"
#include "jsr.h"
#include "ldi.h"
#include "ldr.h"
#include "lea.h"
#include "load.h"
#include "not.h"
#include "sti.h"
#include "store.h"
#include "str.h"
#include "trap.h"

uint16_t check_key()
{
  fd_set readfds;
  FD_ZERO(&readfds);
  FD_SET(STDIN_FILENO, &readfds);

  struct timeval timeout;
  timeout.tv_sec = 0;
  timeout.tv_usec = 0;
  return select(1, &readfds, NULL, NULL, &timeout) != 0;
}

struct termios original_tio;

void disable_input_buffering()
{
  tcgetattr(STDIN_FILENO, &original_tio);
  struct termios new_tio = original_tio;
  new_tio.c_lflag &= ~ICANON & ~ECHO;
  tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
}

void restore_input_buffering()
{
  tcsetattr(STDIN_FILENO, TCSANOW, &original_tio);
}
void handle_interrupt(int signal)
{
  restore_input_buffering();
  printf("\n");
  exit(-2);
}

int main(int argc, const char* argv[])
{
  if (argc < 2)
  {
    /* show usage string */
    printf("lc3 [image-file1] ...\n");
    exit(2);
  }

  for (int j = 1; j < argc; ++j)
  {
    if (!read_image(argv[j]))
    {
      printf("failed to load image: %s\n", argv[j]);
      exit(1);
    }
  }

  signal(SIGINT, handle_interrupt);
  disable_input_buffering();
  enum
  {
    OP_BR = 0, /* branch */
    OP_ADD,    /* add  */
    OP_LD,     /* load */
    OP_ST,     /* store */
    OP_JSR,    /* jump register */
    OP_AND,    /* bitwise and */
    OP_LDR,    /* load register */
    OP_STR,    /* store register */
    OP_RTI,    /* unused */
    OP_NOT,    /* bitwise not */
    OP_LDI,    /* load indirect */
    OP_STI,    /* store indirect */
    OP_JMP,    /* jump */
    OP_RES,    /* reserved (unused) */
    OP_LEA,    /* load effective address */
    OP_TRAP    /* execute trap */
  };

  /* since exactly one condition flag should be set at any given time, set the Z flag */
  reg[R_COND] = FL_ZRO;

  /* set the PC to starting position */
  /* 0x3000 is the default */
  enum { PC_START = 0x3000 };
  reg[R_PC] = PC_START;

  int running = 1;
  while (running)
  {
    /* FETCH */
    uint16_t instr = mem_read(reg[R_PC]++);
    uint16_t op = instr >> 12;

    switch (op)
    {
      case OP_ADD:
        {
          add(instr); 
        }
        break;
      case OP_AND:
        {
          and(instr); 
        }
        break;
      case OP_NOT:
        {
          not(instr); 
        }
        break;
      case OP_BR:
        {
          conditional_branch(instr); 
        }
        break;
      case OP_JMP:
        {
          jmp_ret(instr); 
        }
        break;
      case OP_JSR:
        {
          jsr(instr); 
        }
        break;
      case OP_LD:
        {
          load(instr); 
        }
        break;
      case OP_LDI:
        {
          ldi(instr); 
        }
        break;
      case OP_LDR:
        {
          ldr(instr); 
        }
        break;
      case OP_LEA:
        {
          lea(instr); 
        }
        break;
      case OP_ST:
        {
          store(instr); 
        }
        break;
      case OP_STI:
        {
          sti(instr); 
        }
        break;
      case OP_STR:
        {
          str(instr); 
        }
        break;
      case OP_TRAP:
        {
          trap(instr); 
        }
        break;
      case OP_RES:
      case OP_RTI:
      default:
        abort();
        break;
    }
  }
  restore_input_buffering();
}
