#include <check.h>
#include <unistd.h>
#include <stdlib.h>

#include "../../src/not.h"
#include "../../src/vm.h"
#include "not_test.h"

START_TEST(it_stores_bitwise_complement_of_SR_to_DR_and_sets_CC)
{
  // Arrange
  uint16_t instr=0b1001010001111111;
  reg[0b001] = 0b0101010101010101;
  reg[R_COND] = FL_ZRO;
  // Act
  not(instr);
  // Assert
  ck_assert_int_eq(reg[0b010], 0b1010101010101010);
  ck_assert_int_eq(reg[R_COND], FL_NEG);
}
END_TEST

Suite *make_not_test_suite()
{
  Suite *s;
  TCase *tc;

  s = suite_create("Not");
  tc = tcase_create("Core");

  tcase_add_test(tc, it_stores_bitwise_complement_of_SR_to_DR_and_sets_CC);

  suite_add_tcase(s, tc);

  return s;
}

