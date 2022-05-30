#include <check.h>
#include <unistd.h>
#include <stdlib.h>

#include "../../src/store.h"
#include "../../src/vm.h"
#include "../../src/memory.h"

#include "store_test.h"

START_TEST(it_stores_value_from_SR_in_mem_address_of_new_computed_offset)
{
  // Arrange
  uint16_t instr=0b0011010010101010;
  reg[0b010] = 0b1111111111111111;
  reg[R_PC] = 20;
  // Act
  store(instr);
  // Assert
  ck_assert_int_eq(mem_read(20 + 0b010101010), reg[0b010]);
}
END_TEST

Suite *make_store_test_suite()
{
  Suite *s;
  TCase *tc;

  s = suite_create("Store");
  tc = tcase_create("Core");

  tcase_add_test(tc, it_stores_value_from_SR_in_mem_address_of_new_computed_offset);

  suite_add_tcase(s, tc);

  return s;
}

