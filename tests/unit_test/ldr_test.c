#include <check.h>
#include <unistd.h>
#include <stdlib.h>

#include "../../src/vm.h"
#include "../../src/memory.h"

#include "../../src/ldr.h"
#include "ldr_test.h"

START_TEST(it_loads_from_memory_into_register_and_sets_flags)
{
  // Arrange
  uint16_t instr=0b0110000001010101;
  reg[R_R0] = 0;
  reg[R_R1] = 2;
  reg[R_COND] = FL_ZRO;
  mem_write(23, 0b010);
  // Act
  ldr(instr);
  // Assert
  ck_assert_int_eq(reg[R_R0], 0b010);
  ck_assert_int_eq(reg[R_COND], FL_POS);
}
END_TEST

Suite *make_ldr_test_suite()
{
  Suite *s;
  TCase *tc;

  s = suite_create("Ldr");
  tc = tcase_create("Core");

  tcase_add_test(tc, it_loads_from_memory_into_register_and_sets_flags);

  suite_add_tcase(s, tc);

  return s;
}

