module=${1,,}
module_cap=${module^^}

echo $module
echo $module_cap

echo "#ifndef ${module_cap}_H" > src/$module.h
echo "#define ${module_cap}_H" >> src/$module.h
echo "" >> src/$module.h
echo "#include <stdint.h>" >> src/$module.h
echo "" >> src/$module.h
echo "void $module(uint16_t instr);" >> src/$module.h
echo "" >> src/$module.h
echo "#endif // ${module_cap}_H" >> src/$module.h
echo "" >> src/$module.h

echo "#include <stdlib.h>" > src/$module.c
echo "" >> src/$module.c
echo "#include \"$module.h\"" >> src/$module.c
echo "" >> src/$module.c
echo "void $module(uint16_t instr) {" >> src/$module.c
echo "}" >> src/$module.c
echo "" >> src/$module.c

echo "#ifndef ${module_cap}_TEST_H" > tests/unit_test/${module}_test.h
echo "#define ${module_cap}_TEST_H" >> tests/unit_test/${module}_test.h
echo "" >> tests/unit_test/${module}_test.h
echo "#include <check.h>" >> tests/unit_test/${module}_test.h
echo "" >> tests/unit_test/${module}_test.h
echo "Suite *make_${module}_test_suite();" >> tests/unit_test/${module}_test.h
echo "" >> tests/unit_test/${module}_test.h
echo "#endif // ${module_cap}_TEST_H" >> tests/unit_test/${module}_test.h

echo "#include <check.h>" > tests/unit_test/${module}_test.c
echo "#include <unistd.h>" >> tests/unit_test/${module}_test.c
echo "#include <stdlib.h>" >> tests/unit_test/${module}_test.c
echo "" >> tests/unit_test/${module}_test.c
echo "#include \"../../src/$module.h\"" >> tests/unit_test/${module}_test.c
echo "#include \"${module}_test.h\"" >> tests/unit_test/${module}_test.c
echo "" >> tests/unit_test/${module}_test.c
echo "START_TEST(it_is_an_entrypoint)" >> tests/unit_test/${module}_test.c
echo "{" >> tests/unit_test/${module}_test.c
echo "// Arrange" >> tests/unit_test/${module}_test.c
echo "// Act" >> tests/unit_test/${module}_test.c
echo "// Assert" >> tests/unit_test/${module}_test.c
echo "}" >> tests/unit_test/${module}_test.c
echo "END_TEST" >> tests/unit_test/${module}_test.c
echo "" >> tests/unit_test/${module}_test.c
echo "Suite *make_${module}_test_suite()" >> tests/unit_test/${module}_test.c
echo "{" >> tests/unit_test/${module}_test.c
echo "  Suite *s;" >> tests/unit_test/${module}_test.c
echo "  TCase *tc;" >> tests/unit_test/${module}_test.c
echo "" >> tests/unit_test/${module}_test.c
echo "  s = suite_create(\"${module^}\");" >> tests/unit_test/${module}_test.c
echo "  tc = tcase_create(\"Core\");" >> tests/unit_test/${module}_test.c
echo "" >> tests/unit_test/${module}_test.c
echo "  tcase_add_test(tc, it_is_an_entrypoint);" >> tests/unit_test/${module}_test.c
echo "" >> tests/unit_test/${module}_test.c
echo "  suite_add_tcase(s, tc);" >> tests/unit_test/${module}_test.c
echo "" >> tests/unit_test/${module}_test.c
echo "  return s;" >> tests/unit_test/${module}_test.c
echo "}" >> tests/unit_test/${module}_test.c
echo "" >> tests/unit_test/${module}_test.c
