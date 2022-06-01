#include <check.h>
#include <stdlib.h>

#include "sign_extend_test.h"
#include "update_flags_test.h"
#include "add_test.h"
#include "memory_test.h"
#include "ldi_test.h"
#include "and_test.h"
#include "conditional_branch_test.h"
#include "jmp_ret_test.h"
#include "jsr_test.h"
#include "load_test.h"
#include "lea_test.h"
#include "not_test.h"
#include "store_test.h"
#include "sti_test.h"
#include "str_test.h"
#include "trap_test.h"

int main()
{
    int number_failed;
    SRunner *sr;

    sr = srunner_create(make_sign_extend_test_suite());
    srunner_add_suite(sr, make_update_flags_test_suite());
    srunner_add_suite(sr, make_add_test_suite());
    srunner_add_suite(sr, make_memory_test_suite());
    srunner_add_suite(sr, make_ldi_test_suite());
    srunner_add_suite(sr, make_and_test_suite());
    srunner_add_suite(sr, make_conditional_branch_test_suite());
    srunner_add_suite(sr, make_jmp_ret_test_suite());
    srunner_add_suite(sr, make_jsr_test_suite());
    srunner_add_suite(sr, make_load_test_suite());
    srunner_add_suite(sr, make_lea_test_suite());
    srunner_add_suite(sr, make_not_test_suite());
    srunner_add_suite(sr, make_store_test_suite());
    srunner_add_suite(sr, make_sti_test_suite());
    srunner_add_suite(sr, make_str_test_suite());
    srunner_add_suite(sr, make_trap_test_suite());

    srunner_run_all(sr, CK_NORMAL);

    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed==0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
