#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int tests_passed;
    int tests_failed;
} Tests;

Tests test;

void print_summary(Tests* test) {
    printf("RAN %d TESTS\n", test->tests_passed + test->tests_failed);
    printf("PASSED %d FAILED %d\n", test->tests_passed, test->tests_failed);
}

void assert(const char* test_name, bool condition) {
    if (condition) {
        test.tests_passed += 1;
        fprintf(stderr, "PASSED ... '%s'\n", test_name);
    } else {
        test.tests_failed += 1;
        fprintf(stderr, "FAILED ... '%s'\n", test_name);       
    }
}

int main() {
    test.tests_passed = 0;
    test.tests_failed = 0;

    assert("1 == 1", 1 == 1);
    assert("2 == 2", 2 == 2);

    print_summary(&test);
}
