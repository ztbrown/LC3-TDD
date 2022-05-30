#include <check.h>
#include <unistd.h>
#include <stdlib.h>

#include "../../src/str.h"
#include "../../src/memory.h"
#include "../../src/vm.h"
#include "str_test.h"

START_TEST(it_stores_SR_value_in_mem_address_of_BaseR_plus_offset)
{
  // Arrange
  uint16_t instr=0b0111010001010101;
  reg[0b001]=1;
  reg[0b010]=0xFFFF;
  // Act
  str(instr);
  // Assert
  ck_assert_int_eq(mem_read(0b010110), 0xFFFF);
}
END_TEST

Suite *make_str_test_suite()
{
  Suite *s;
  TCase *tc;

  s = suite_create("Str");
  tc = tcase_create("Core");

  tcase_add_test(tc, it_stores_SR_value_in_mem_address_of_BaseR_plus_offset);

  suite_add_tcase(s, tc);

  return s;
}

