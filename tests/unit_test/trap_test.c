#include <check.h>
#include <unistd.h>
#include <stdlib.h>

#include "../../lib/mock.h"

#include "../../src/trap.h"
#include "../../src/memory.h"
#include "../../src/prompt.h"
#include "../../src/vm.h"
#include "trap_test.h"

SIMULACRUM(void *, getchar, 0)
SIMULACRUM(void *, putchar, 1, int)
SIMULACRUM(void, prompt, 1, const char *)

static void setup()
{
  mock_off(&getchar_mock);
  mock_off(&putchar_mock);
  mock_off(&prompt_mock);
}

static void teardown()
{
  mock_reset_call_count(&getchar_mock);
  mock_reset_call_count(&putchar_mock);
  mock_reset_call_count(&prompt_mock);
}

int trap_out_c=0;
// putchar_mock delegates to callback and passes argument 
static void putchar_callback(int c) {
  trap_out_c = c;
}

START_TEST(it_gets_character_from_keyboard_TRAP_GETC)
{
  // Arrange
  uint16_t instr=0b1111000000100000;
  uint16_t rtn = 0b0000000000000001;
  reg[R_R0]=0;

  mock_on(&getchar_mock);
  mock_set_return_value(&getchar_mock, &rtn);

  // Act
  trap(instr);

  // Assert
  ck_assert_int_eq(mock_get_call_count(&getchar_mock), 1);
  ck_assert_int_eq(reg[R_R0], 1);
}
END_TEST

START_TEST(it_puts_character_from_register_TRAP_OUT)
{
  // Arrange
  uint16_t instr=0b1111000000100001;
  uint16_t rtn = 0b0000000000000001;
  reg[R_R0]=1;

  mock_on(&putchar_mock);
  mock_set_return_value(&putchar_mock, &rtn);
  mock_set_callback(&putchar_mock, &putchar_callback);

  // Act
  trap(instr);

  // Assert
  ck_assert_int_eq(mock_get_call_count(&putchar_mock), 1);
  ck_assert_int_eq(trap_out_c, reg[R_R0]);
}
END_TEST

START_TEST(it_puts_string_from_mem_locations_beginning_with_R0_TRAP_PUTS)
{
  // Arrange
  uint16_t instr=0b1111000000100010;
  mem_write(1, 0b0000000001101000);
  mem_write(2, 0b0000000001100101);
  mem_write(3, 0b0000000001101100);
  mem_write(4, 0b0000000001101100);
  mem_write(5, 0b0000000001101111);
  mem_write(6, 0b0000000000000000);
  reg[R_R0]=1;

  mock_on(&putchar_mock);

  // Act
  trap(instr);

  // Assert
  ck_assert_int_eq(mock_get_call_count(&putchar_mock), 5);
}
END_TEST

START_TEST(it_reads_character_and_writes_it_to_console_and_R0_TRAP_IN)
{
  // Arrange
  uint16_t instr=0b1111000000100011;
  uint16_t rtn = 0b0000000000000001;
  reg[R_R0]=0;
  reg[R_COND]=FL_ZRO;

  mock_on(&putchar_mock);
  mock_on(&getchar_mock);
  mock_on(&prompt_mock);
  mock_set_return_value(&getchar_mock, &rtn);

  // Act
  trap(instr);

  // Assert
  ck_assert_int_eq(mock_get_call_count(&getchar_mock), 1);
  ck_assert_int_eq(mock_get_call_count(&putchar_mock), 1);
  ck_assert_int_eq(mock_get_call_count(&prompt_mock), 1);
  ck_assert_int_eq(trap_out_c, reg[R_R0]);
  ck_assert_int_eq(reg[R_COND], FL_POS);
}
END_TEST

START_TEST(it_reads_characters_two_at_a_time_from_memory_and_outputs_to_console_TRAP_PUTSP)
{
  // Arrange
  uint16_t instr=0b1111000000100100;
  mem_write(1, 0b0110010101101000);
  mem_write(2, 0b0110110001101100);
  mem_write(3, 0b0010000001101111);
  mem_write(4, 0b0110111101110111);
  mem_write(5, 0b0110110001110010);
  mem_write(6, 0b0000000001100100);
  mem_write(7, 0b0000000000000000);
  reg[R_R0]=1;

  mock_on(&putchar_mock);
  mock_on(&getchar_mock);

  // Act
  trap(instr);

  // Assert
  // hello world
  ck_assert_int_eq(mock_get_call_count(&putchar_mock), 12);
}
END_TEST

START_TEST(it_halts_the_vm_TRAP_HALT)
{
  // Arrange
  uint16_t instr=0b1111000000100101;
  reg[R_R0]=1;

  mock_on(&prompt_mock);

  // Act
  trap(instr);

  // Assert
  ck_assert_int_eq(mock_get_call_count(&prompt_mock), 1);
  ck_assert_int_eq(running, 0);
}
END_TEST

Suite *make_trap_test_suite()
{
  Suite *s;
  TCase *tc;

  s = suite_create("Trap");
  tc = tcase_create("Core");

  tcase_add_checked_fixture(tc, &setup, &teardown);

  tcase_add_test(tc, it_gets_character_from_keyboard_TRAP_GETC);
  tcase_add_test(tc, it_puts_character_from_register_TRAP_OUT);
  tcase_add_test(tc, it_puts_string_from_mem_locations_beginning_with_R0_TRAP_PUTS);
  tcase_add_test(tc, it_reads_character_and_writes_it_to_console_and_R0_TRAP_IN);
  tcase_add_test(tc, it_reads_characters_two_at_a_time_from_memory_and_outputs_to_console_TRAP_PUTSP);
  tcase_add_test(tc, it_halts_the_vm_TRAP_HALT);

  suite_add_tcase(s, tc);

  return s;
}

