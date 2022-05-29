#include <check.h>
#include <unistd.h>
#include <stdlib.h>

#include "../../src/vm.h"
#include "../../src/memory.h"
#include "../../src/ldi.h"

#include "ldi_test.h"

START_TEST(it_loads_memory_location_into_register)
{
  //Arrange
  uint16_t value=0b1010101010101010;
  uint16_t result;
  // instruction 1010 DR 001 pcoffset 000000001
  uint16_t instr=0b1010001000000001;
  mem_write(1, 2);
  mem_write(2, value);
  reg[R_PC] = 0;

  // Act
  ldi(instr);

  // Assert
  ck_assert_int_eq(reg[001], value);
}
END_TEST

START_TEST(it_updates_the_flags)
{
  //Arrange
  uint16_t value=0b0010101010101010;
  uint16_t result;
  // instruction 1010 DR 001 pcoffset 000000001
  uint16_t instr=0b1010001000000001;
  mem_write(1, 2);
  mem_write(2, value);
  reg[R_PC] = 0;
  reg[R_COND] = FL_ZRO;

  // Act
  ldi(instr);

  // Assert
  ck_assert_int_eq(reg[R_COND], FL_POS);
}
END_TEST

Suite *make_ldi_test_suite()
{
  Suite *s;
  TCase *tc;

  s = suite_create("LDI");
  tc = tcase_create("Core");

  tcase_add_test(tc, it_loads_memory_location_into_register);
  tcase_add_test(tc, it_updates_the_flags);

  suite_add_tcase(s, tc);

  return s;
}
