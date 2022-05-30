#include <check.h>
#include <unistd.h>
#include <stdlib.h>

#include "jmp_ret_test.h"

#include "../../src/vm.h"
#include "../../src/jmp_ret.h"

START_TEST(it_unconditionally_jumps_to_base_register)
{
  //Arrange
  uint16_t instr=0b1100000000000000;
  reg[R_PC] = 0;
  reg[R_R0] = 0xfff;

  // Act
  jmp_ret(instr);

  // Assert
  ck_assert_int_eq(reg[R_PC], 0xfff);
}
END_TEST

Suite *make_jmp_ret_test_suite()
{
  Suite *s;
  TCase *tc;

  s = suite_create("Memory");
  tc = tcase_create("Core");

  tcase_add_test(tc, it_unconditionally_jumps_to_base_register);

  suite_add_tcase(s, tc);

  return s;
}
