#include <stdlib.h>

#include "unity.h"
#include "processing.h"
#include "appointments.h"

void test_current_day() {
	char* day = (char*) malloc(4 * sizeof(char));
	day = current_day();
	TEST_ASSERT_EQUAL_STRING("Fri", day);
}

void setUp() {
	 //this function is called before each test, it can be empty
}

void tearDown() {
	 //this function is called after each test, it can be empty
}

int main() {
	UNITY_BEGIN();

	RUN_TEST(test_current_day);

	return UNITY_END();
}