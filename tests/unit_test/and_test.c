#include <check.h>
#include <unistd.h>
#include <stdlib.h>

#include "and_test.h"

#include "../../src/vm.h"

#include "../../src/and.h"

START_TEST(it_compares_two_equivalent_values_and_stores_the_result)
{
  //Arrange
  uint16_t instr=0b0101001010000011;
  reg[0b010] = 0xFFF;
  reg[0b011] = 0xFFF;

  // Act
  and(instr);

  // Assert
  ck_assert_int_eq(reg[0b001], 0xFFF);
}
END_TEST

START_TEST(it_compares_equivalents_in_register_and_imm5)
{
  //Arrange
  uint16_t instr=0b0101001010111111;
  reg[0b010] = 0b11111;

  // Act
  and(instr);

  // Assert
  ck_assert_int_eq(reg[0b001], 0b11111);
}
END_TEST

START_TEST(it_updates_the_flags)
{
  //Arrange
  uint16_t instr=0b0101001010111111;
  reg[0b010] = 0xFFFF;
  reg[R_COND] = FL_ZRO;

  // Act
  and(instr);

  // Assert
  ck_assert_int_eq(reg[R_COND], FL_NEG);
}
END_TEST

Suite *make_and_test_suite()
{
  Suite *s;
  TCase *tc;

  s = suite_create("And");
  tc = tcase_create("Core");

  tcase_add_test(tc, it_compares_two_equivalent_values_and_stores_the_result);
  tcase_add_test(tc, it_compares_equivalents_in_register_and_imm5);
  tcase_add_test(tc, it_updates_the_flags);

  suite_add_tcase(s, tc);

  return s;
}
