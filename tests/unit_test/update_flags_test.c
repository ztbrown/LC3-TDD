#include <check.h>
#include <unistd.h>
#include <stdlib.h>

#include "../../src/update_flags.h"
#include "../../src/vm.h"
#include "update_flags_test.h"

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
