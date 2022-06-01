#include <check.h>
#include <unistd.h>
#include <stdlib.h>

#include "../../src/image.h"
#include "image_test.h"

START_TEST(it_writes_the_given_image_path_to_a_file_buffer)
{
  // Arrange
  const char *path = "some image path";
  int rtn = 0;
   
  // Act
  read_image(path);

  // Assert
 // ck_assert_int_eq(mock_get_call_count(&fopen_mock), 1);
  ck_assert_int_eq(rtn, 1);
}
END_TEST

Suite *make_image_test_suite()
{
  Suite *s;
  TCase *tc;

  s = suite_create("Image");
  tc = tcase_create("Core");

//  tcase_add_checked_fixture(tc, &setup, &teardown);

  tcase_add_test(tc, it_writes_the_given_image_path_to_a_file_buffer);

  suite_add_tcase(s, tc);

  return s;
}

