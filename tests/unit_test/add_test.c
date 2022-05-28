#include <check.h>
#include <unistd.h>
#include <stdlib.h>

#include "../../src/add.h"
#include "../../src/vm.h"
#include "add_test.h"

START_TEST(it_adds_register_to_imm5)
{
  //Arrange
  uint16_t instr=0b0001000001100001;
  reg[R_R0] = 0;
  reg[R_R1] = 1;

  // Act
  add(instr);

  // Assert
  ck_assert_int_eq(reg[R_R0], 2);
}
END_TEST

START_TEST(it_sign_extends_the_imm5)
{
  //Arrange
  uint16_t instr=0b0001000001110001;
  reg[R_R0] = 0;
  reg[R_R1] = 0;

  // Act
  add(instr);

  // Assert
  ck_assert_int_eq(reg[R_R0], 0b1111111111110001);
}
END_TEST

START_TEST(it_updates_the_flags)
{
  //Arrange
  uint16_t instr=0b0001000001110001;
  reg[R_R0] = 0;
  reg[R_R1] = 0;
  reg[R_COND] = FL_ZRO;

  // Act
  add(instr);

  // Assert
  ck_assert_int_eq(reg[R_R0], 0b1111111111110001);
  ck_assert_int_eq(reg[R_COND], FL_NEG);
}
END_TEST

START_TEST(it_adds_two_source_registers)
{
  //Arrange
  uint16_t instr=0b0001000001000010;
  reg[R_R0] = 0;
  reg[R_R1] = 1;
  reg[R_R2] = 1;

  // Act
  add(instr);

  // Assert
  ck_assert_int_eq(reg[R_R0], 2);
}
END_TEST

Suite *make_add_test_suite()
{
  Suite *s;
  TCase *tc;

  s = suite_create("Add");
  tc = tcase_create("Core");

  tcase_add_test(tc, it_adds_register_to_imm5);
  tcase_add_test(tc, it_sign_extends_the_imm5);
  tcase_add_test(tc, it_updates_the_flags);
  tcase_add_test(tc, it_adds_two_source_registers);

  suite_add_tcase(s, tc);

  return s;
}
