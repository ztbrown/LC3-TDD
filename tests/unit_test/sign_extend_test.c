#include <check.h>
#include <unistd.h>
#include <stdlib.h>

#include "sign_extend_test.h"

uint16_t sign_extend(uint16_t number) {
  int bit_count = 5;
  if ((number >> (bit_count - 1)) & 1) {
    number |= (0xFFFF << bit_count);
  }
  return number;
}

START_TEST(it_extends_a_positive_number_with_0s)
{
  // Arrange
  uint16_t instr = 0b00001;
  uint16_t result;

  // Act
  result = sign_extend(instr);

  // Assert
  ck_assert_int_eq(result, 0b0000000000000001);
}
END_TEST

START_TEST(it_extends_a_negative_number_with_1s)
{
  // Arrange
  uint16_t instr = 0b10001;
  uint16_t result;

  // Act
  result = sign_extend(instr);

  // Assert
  ck_assert_int_eq(result, 0b1111111111110001);
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
