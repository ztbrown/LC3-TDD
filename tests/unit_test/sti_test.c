#include <check.h>
#include <unistd.h>
#include <stdlib.h>

#include "../../src/sti.h"
#include "../../src/memory.h"
#include "../../src/vm.h"

#include "sti_test.h"

START_TEST(it_is_an_entrypoint)
{
  // Arrange
  uint16_t instr=0b1011010010101010;
  reg[R_PC] = 0b10100;
  reg[0b010] = 0b1111111111111111;
  mem_write(0b010111110, 0xa);

  // Act
  sti(instr);
  // Assert
  ck_assert_int_eq(mem_read(0xa), 0b1111111111111111);
}
END_TEST

Suite *make_sti_test_suite()
{
  Suite *s;
  TCase *tc;

  s = suite_create("Sti");
  tc = tcase_create("Core");

  tcase_add_test(tc, it_is_an_entrypoint);

  suite_add_tcase(s, tc);

  return s;
}

