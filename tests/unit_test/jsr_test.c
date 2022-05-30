#include <check.h>
#include <unistd.h>
#include <stdlib.h>

#include "../../src/jsr.h"
#include "../../src/vm.h"
#include "jsr_test.h"

START_TEST(it_jumps_to_pcoffset_after_storing_current_PC_in_R7)
{
  //Arrange
  uint16_t instr=0b0100101010101010;
  reg[R_R7] = 0; 
  reg[R_PC] = 0b0000000000000001;

  // Act
  jsr(instr);

  // Assert
  ck_assert_int_eq(reg[R_PC], 0b0000001010101011);
  ck_assert_int_eq(reg[R_R7], 1); 
}
END_TEST

START_TEST(it_jumps_to_baser_after_storing_current_PC_in_R7)
{
  //Arrange
  uint16_t instr=0b0100000010000000;
  int baseR = 0b010;
  reg[R_R7] = 0;
  reg[baseR] = 0xfff;
  reg[R_PC] = 0b0000000000000001;

  // Act
  jsr(instr);

  // Assert
  ck_assert_int_eq(reg[R_PC], 0xfff);
  ck_assert_int_eq(reg[R_R7], 1); 
}
END_TEST

Suite *make_jsr_test_suite()
{
  Suite *s;
  TCase *tc;

  s = suite_create("Memory");
  tc = tcase_create("Core");

  tcase_add_test(tc, it_jumps_to_pcoffset_after_storing_current_PC_in_R7);
  tcase_add_test(tc, it_jumps_to_baser_after_storing_current_PC_in_R7);

  suite_add_tcase(s, tc);

  return s;
}
