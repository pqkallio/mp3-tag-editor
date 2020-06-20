#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

CU_SuiteInfo create_test_suite(char* name, CU_TestInfo* tests)
{
    CU_SuiteInfo info = { name, NULL, NULL, NULL, NULL, tests };

    return info;
}

int main()
{
    CU_ErrorCode err = CU_initialize_registry();

    if (err != CUE_SUCCESS) {
        return err;
    }

    CU_SuiteInfo suites[] = {};

    err = CU_register_suites(suites);

    if (err != CUE_SUCCESS) {
        CU_cleanup_registry();
        return err;
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    CU_cleanup_registry();

    return CU_get_error();
}
