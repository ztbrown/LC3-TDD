#include <check.h>
#include <unistd.h>
#include <stdlib.h>

#include "update_flags_test.h"

enum
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

uint16_t reg[R_COUNT];

enum
{
  FL_POS = 1 << 0, /* P */
  FL_ZRO = 1 << 1, /* Z */
  FL_NEG = 1 << 2, /* N */
};

uint16_t update_flags(uint16_t r) {
  if (reg[r] == 0) {
    reg[R_COND] = FL_ZRO;
  } 
  else if (reg[r] >> 15) {
    reg[R_COND] = FL_NEG;
  }
  else {
    reg[R_COND] = FL_POS;
  } 
}

START_TEST(it_sets_register_to_ZRO_if_result_zero)
{
  // Act
  update_flags(R_R0);

  // Assert
  ck_assert_int_eq(reg[R_COND], FL_ZRO);
}
END_TEST

START_TEST(it_sets_register_to_POS_if_result_greater_than_zero)
{
  // Arrange
  reg[R_R0] = 0b0000000000000001;

  // Act
  update_flags(R_R0);

  // Assert
  ck_assert_int_eq(reg[R_COND], FL_POS);
}
END_TEST

START_TEST(it_sets_register_to_NEG_if_result_less_than_zero)
{
  // Arrange
  reg[R_R0] = 0b1000000000000001;

  // Act
  update_flags(R_R0);

  // Assert
  ck_assert_int_eq(reg[R_COND], FL_NEG);
}
END_TEST


Suite *make_update_flags_test_suite()
{
  Suite *s;
  TCase *tc;

  s = suite_create("Update flags");
  tc = tcase_create("Core");

  tcase_add_test(tc, it_sets_register_to_ZRO_if_result_zero);
  tcase_add_test(tc, it_sets_register_to_POS_if_result_greater_than_zero);
  tcase_add_test(tc, it_sets_register_to_NEG_if_result_less_than_zero);

  suite_add_tcase(s, tc);

  return s;
}
