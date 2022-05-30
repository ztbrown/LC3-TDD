#include <check.h>
#include <unistd.h>
#include <stdlib.h>

#include "../../src/vm.h"
#include "../../src/lea.h"
#include "lea_test.h"

START_TEST(it_loads_the_computed_offset_into_the_DR_and_sets_CC)
{
  //Arrange 
  uint16_t instr=0b1110010010101010;
  reg[R_PC] = 20;
  reg[R_COND] = FL_ZRO;
  reg[0b010] = 0;

  //Act
  lea(instr);
  
  //Assert
  ck_assert_int_eq(reg[0b010], 20 + 0b010101010);
  ck_assert_int_eq(reg[R_COND], FL_POS);

}
END_TEST

Suite *make_lea_test_suite()
{
  Suite *s;
  TCase *tc;

  s = suite_create("Lea");
  tc = tcase_create("Core");

  tcase_add_test(tc, it_loads_the_computed_offset_into_the_DR_and_sets_CC);

  suite_add_tcase(s, tc);

  return s;
}

