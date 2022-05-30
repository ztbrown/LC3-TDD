#include <check.h>
#include <unistd.h>
#include <stdlib.h>

#include "conditional_branch_test.h"

#include "../../src/vm.h"
#include "../../src/conditional_branch.h"

START_TEST(it_branches_when_condition_flag_passes)
{
  //Arrange
  uint16_t instr=0b0000100010101010;
  reg[R_PC] = 0;
  reg[R_COND] = FL_NEG;

  // Act
  conditional_branch(instr);

  // Assert
  ck_assert_int_eq(reg[R_PC], 0b0000000010101010);
}
END_TEST

START_TEST(it_doesnt_branch_when_condition_flag_fails)
{
  //Arrange
  uint16_t instr=0b0000100010101010;
  reg[R_PC] = 0;
  reg[R_COND] = FL_POS;

  // Act
  conditional_branch(instr);

  // Assert
  ck_assert_int_eq(reg[R_PC], 0);
}
END_TEST

Suite *make_conditional_branch_test_suite()
{
  Suite *s;
  TCase *tc;

  s = suite_create("Conditional branch");
  tc = tcase_create("Core");

  tcase_add_test(tc, it_branches_when_condition_flag_passes);
  tcase_add_test(tc, it_doesnt_branch_when_condition_flag_fails);

  suite_add_tcase(s, tc);

  return s;
}
