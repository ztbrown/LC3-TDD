#include <check.h>
#include <unistd.h>
#include <stdlib.h>

#include "sign_extend_test.h"

#include "../../src/sign_extend.h"

START_TEST(it_extends_a_positive_number_with_0s)
{
  // Arrange
  uint16_t instr = 0b00001;
  uint16_t result;

  // Act
  result = sign_extend(instr, 5);

  // Assert
  ck_assert_int_eq(result, 0b0000000000000001);
}
END_TEST

START_TEST(it_extends_a_negative_number_with_1s)
{
  // Arrange
  uint16_t instr = 0b100001;
  uint16_t result;

  // Act
  result = sign_extend(instr, 6);

  // Assert
  ck_assert_int_eq(result, 0b1111111111100001);
}
END_TEST

Suite *make_sign_extend_test_suite()
{
  Suite *s;
  TCase *tc;

  s = suite_create("Sign Extend");
  tc = tcase_create("Core");

  tcase_add_test(tc, it_extends_a_positive_number_with_0s);
  tcase_add_test(tc, it_extends_a_negative_number_with_1s);

  suite_add_tcase(s, tc);

  return s;
}
