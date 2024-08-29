#include "deploy_rc4.h"
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

unsigned char shellcode[] = {"This is the shellcode that is used for rc4 encryption !"};
unsigned char key[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};

int init_suite1(void)
{
    return 0;
}

int clean_suite1(void)
{
    return 0;
}

void test_rc4Init(void)
{
    Rc4Context context;
    rc4Init(&context, key, sizeof(key));
    for (int i = 0; i < BUF_MAX; i++)
    {
        printf(" %d", context.arr[i]);
    }
}

void test_rc4Cipher(void)
{
    Rc4Context context;
    rc4Init(&context, key, sizeof(key));
    rc4Cipher(&context, shellcode, shellcode, sizeof(shellcode));
    for (int i = 0; i < BUF_MAX; i++)
    {
        printf(" %d", context.arr[i]);
    }
}

int main()
{
    CU_TestInfo suite1_tests[] = {{"Test printing rc4 contents after rc4init: ", test_rc4Init},
                                  {"Test printing rc4 contents after rc4cipher: ", test_rc4Cipher},
                                  CU_TEST_INFO_NULL};

    CU_SuiteInfo suites[] = {{"Suite-1:", init_suite1, clean_suite1, .pTests = suite1_tests}, CU_SUITE_INFO_NULL};

    if (0 != CU_initialize_registry())
    {
        return CU_get_error();
    }

    if (0 != CU_register_suites(suites))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);

    CU_basic_run_tests();
    CU_basic_show_failures(CU_get_failure_list());

    int num_failed = CU_get_number_of_failures();
    CU_cleanup_registry();
    printf("\n");
    return num_failed;
}