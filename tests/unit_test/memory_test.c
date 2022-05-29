#include <check.h>
#include <unistd.h>
#include <stdlib.h>

#include "../../src/memory.h"
#include "memory_test.h"

START_TEST(it_reads_from_memory)
{
  //Arrange
  uint16_t address=0;
  uint16_t result;
  mem_write(address, 1 << 15);

  // Act
  result = mem_read(address);

  // Assert
  ck_assert_int_eq(result, 1 << 15);
}
END_TEST

START_TEST(it_writes_to_memory)
{
  //Arrange
  uint16_t address=0;
  uint16_t value=0b1111111111111111;
  uint16_t result;

  // Act
  mem_write(address, value);
  result = mem_read(address);

  // Assert
  ck_assert_int_eq(result, value);
}
END_TEST

Suite *make_memory_test_suite()
{
  Suite *s;
  TCase *tc;

  s = suite_create("Memory");
  tc = tcase_create("Core");

  tcase_add_test(tc, it_reads_from_memory);
  tcase_add_test(tc, it_writes_to_memory);

  suite_add_tcase(s, tc);

  return s;
}
