#include <check.h>
#include <unistd.h>
#include <stdlib.h>

#include "../../src/load.h"
#include "../../src/vm.h"

#include "load_test.h"

START_TEST(it_loads_new_PC_to_DR_and_checks_condition_flags)
{
  //Arrange
  uint16_t instr=0b0010010010101010;
  reg[R_PC] = 0b010;
  reg[R_COND] = FL_ZRO;

  // Act
  load(instr);

  // Assert
  ck_assert_int_eq(reg[0b010], 0b010101010);
  ck_assert_int_eq(reg[R_COND], FL_POS);
}
END_TEST

Suite *make_load_test_suite()
{
  Suite *s;
  TCase *tc;

  s = suite_create("LD");
  tc = tcase_create("Core");

  tcase_add_test(tc, it_loads_new_PC_to_DR_and_checks_condition_flags);

  suite_add_tcase(s, tc);

  return s;
}
