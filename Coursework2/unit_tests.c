#include <stdlib.h>
#include <time.h>

#include "unity.h"
#include "processing.h"
#include "appointments.h"
#include "replies.h"

//---------------------------------------------------------------------------------------
// Appointments Module
//---------------------------------------------------------------------------------------

void test_current_day() {
	char* day = (char*) malloc(4 * sizeof(char));
	day = current_day();
	TEST_ASSERT_EQUAL_STRING("Fri", day);
}

void test_string_to_sec() {
	time_t t = string_to_sec("17.06.2021");
	struct tm tm = string_to_tm("17.06.2021");
	time_t t1 = mktime(&tm); 
	TEST_ASSERT_EQUAL_INT(t1, t);
}

void test_string_to_tm() {
	struct tm tm = string_to_tm("17.06.2021");
	TEST_ASSERT_EQUAL_INT(17, tm.tm_mday);
	TEST_ASSERT_EQUAL_INT(6, 1 + tm.tm_mon);
	TEST_ASSERT_EQUAL_INT(2021, 1900 + tm.tm_year);
}

void test_check_availability() {
	int app = load_appointments();
	int doc = load_doctors();
	TEST_ASSERT_EQUAL_INT(0, app);
	TEST_ASSERT_EQUAL_INT(0, doc);
	
	int free1 = check_availability("16.04.2021", "09:00", "kelsie martinez");
	int busy1 = check_availability("16.04.2021", "09:30", "kelsie martinez");
	int outside_sch1 = check_availability("16.04.2021", "13:00", "kelsie martinez");
	int free2 = check_availability("08.04.2021", "16:30", "mohamed webster");
	int busy2 = check_availability("06.04.2021", "13:30", "mohamed webster");
	int outside_sch2 = check_availability("07.04.2021", "12:00", "mohamed webster");

	TEST_ASSERT_EQUAL_INT(0, free1);
	TEST_ASSERT_EQUAL_INT(1, busy1);
	TEST_ASSERT_EQUAL_INT(-1, outside_sch1);
	TEST_ASSERT_EQUAL_INT(0, free2);
	TEST_ASSERT_EQUAL_INT(1, busy2);
	TEST_ASSERT_EQUAL_INT(-1, outside_sch2);
}

void test_load_appointments() {
	int a = load_appointments();
	TEST_ASSERT_EQUAL_INT_MESSAGE(0, a, "Error: appointments unsuccessfully loaded!");

	//Edge cases
	TEST_ASSERT_EQUAL_STRING("1001", appointment[0].app_ID);
	TEST_ASSERT_EQUAL_STRING("Rowan Atkinson", appointment[0].name);
	TEST_ASSERT_EQUAL_STRING("07323404154", appointment[0].tel);
	TEST_ASSERT_EQUAL_STRING("1006", appointment[5].app_ID);
	TEST_ASSERT_EQUAL_STRING("otolaryngology", appointment[5].department);
	TEST_ASSERT_EQUAL_STRING("09:30", appointment[5].time);


	//Random Tests
	TEST_ASSERT_EQUAL_STRING("1003", appointment[2].app_ID);
	TEST_ASSERT_EQUAL_STRING("pustianuchristian@yahoo.com", appointment[2].email);
	TEST_ASSERT_EQUAL_STRING("19", appointment[2].age);
	TEST_ASSERT_EQUAL_STRING("06.04.2021", appointment[2].date);
	TEST_ASSERT_EQUAL_STRING("Tue", appointment[2].weekday);
}

void test_load_doctors() {
	int a = load_doctors();
	TEST_ASSERT_EQUAL_INT_MESSAGE(0, a, "Error: doctors unsuccessfully loaded!");

	//Edge cases
	TEST_ASSERT_EQUAL_STRING("orthopedy", department[0].dep_title);
	TEST_ASSERT_EQUAL_STRING("zaara rosales", department[0].doctors[0].full_name);
	TEST_ASSERT_EQUAL_STRING("70", department[0].doctors[0].appointment_price);
	TEST_ASSERT_EQUAL_STRING("Mon", department[0].doctors[0].schedule[0].weekday);
	
	TEST_ASSERT_EQUAL_STRING("85", department[9].doctors[2].appointment_price);
	TEST_ASSERT_EQUAL_STRING("000011110000111111110000", department[9].doctors[2].schedule[2].session);
	//Random Tests
	TEST_ASSERT_EQUAL_STRING("dermatology", department[3].dep_title);
	TEST_ASSERT_EQUAL_STRING("francesco blackwell", department[3].doctors[2].full_name);
	TEST_ASSERT_EQUAL_STRING("70", department[3].doctors[0].appointment_price);
	TEST_ASSERT_EQUAL_STRING("alicja osborn", department[4].doctors[0].full_name);
	TEST_ASSERT_EQUAL_STRING("Mon", department[4].doctors[0].schedule[0].weekday);
	TEST_ASSERT_EQUAL_STRING("Thu", department[4].doctors[1].schedule[1].weekday);
	TEST_ASSERT_EQUAL_STRING("000011110000111111110000", department[4].doctors[1].schedule[1].session);
}

//---------------------------------------------------------------------------------------
// Processing Module
//---------------------------------------------------------------------------------------

void test_search_for_department() {
	current_appointment.department = (char*) malloc(20*sizeof(char));
	TEST_ASSERT_EQUAL_INT(0, search_for_department("endocrinology"));
	TEST_ASSERT_EQUAL_INT(0, search_for_department("orthopedy"));
	TEST_ASSERT_EQUAL_INT(0, search_for_department("neurology"));
	TEST_ASSERT_EQUAL_INT(1, search_for_department("torthopedy"));
	TEST_ASSERT_EQUAL_INT(1, search_for_department("orthopeyd"));
	TEST_ASSERT_EQUAL_INT(1, search_for_department("orthope"));
	
	free(current_appointment.department);
}

void test_search_for_doctor() {
	current_appointment.doctor = (char*) malloc(30*sizeof(char));
	TEST_ASSERT_EQUAL_INT(0, search_for_doctor("colleen", "wall"));
	TEST_ASSERT_EQUAL_INT(0, search_for_doctor("wall", "colleen"));
	TEST_ASSERT_EQUAL_INT(1, search_for_doctor("colleen", "walls"));
	TEST_ASSERT_EQUAL_INT(1, search_for_doctor("tcolleen", "lwall"));
	TEST_ASSERT_EQUAL_INT(1, search_for_doctor("colleen", "colleen"));
	TEST_ASSERT_EQUAL_INT(1, search_for_doctor("wall", "wall"));
	TEST_ASSERT_EQUAL_INT(0, search_for_doctor("mohamed", "webster"));
	TEST_ASSERT_EQUAL_INT(0, search_for_doctor("farmer", "derek"));
	free(current_appointment.doctor);
}

void test_search_for_intent_in_word() {
	TEST_ASSERT_EQUAL_INT(0, search_for_intent_in_word("want"));
	TEST_ASSERT_EQUAL_INT(0, search_for_intent_in_word("wish"));
	TEST_ASSERT_EQUAL_INT(0, search_for_intent_in_word("can"));
	TEST_ASSERT_EQUAL_INT(1, search_for_intent_in_word("wint"));
	TEST_ASSERT_EQUAL_INT(1, search_for_intent_in_word("swish"));
	TEST_ASSERT_EQUAL_INT(1, search_for_intent_in_word("needs"));
}

void test_search_for_intent_in_string() {
	TEST_ASSERT_EQUAL_INT(0, search_for_intent_in_string("I would like to make an appointment."));
	TEST_ASSERT_EQUAL_INT(0, search_for_intent_in_string("I wish for an appointment cancellation."));
	TEST_ASSERT_EQUAL_INT(0, search_for_intent_in_string("I would love to make an appointment."));
	TEST_ASSERT_EQUAL_INT(1, search_for_intent_in_string("I wouldn't like to make an appointment."));
	TEST_ASSERT_EQUAL_INT(1, search_for_intent_in_string("I wish to make an appointment."));
	TEST_ASSERT_EQUAL_INT(0, search_for_intent_in_string("Hello! my friend would like to cancel an appointment."));

}

//---------------------------------------------------------------------------------------
// Replies Module
//---------------------------------------------------------------------------------------

void setUp() {
	 //this function is called before each test, it can be empty
}

void tearDown() {
	 //this function is called after each test, it can be empty
}

int main() {
	UNITY_BEGIN();

	// Appointments Module
	RUN_TEST(test_current_day);
	RUN_TEST(test_string_to_sec);
	RUN_TEST(test_string_to_tm);
	// RUN_TEST(test_check_availability);
	RUN_TEST(test_load_doctors);
	RUN_TEST(test_load_appointments);
	//Processing Module
	RUN_TEST(test_search_for_department);
	RUN_TEST(test_search_for_doctor);
	RUN_TEST(test_search_for_intent_in_word);
	RUN_TEST(test_search_for_intent_in_string);
	// RUN_TEST(test_);
	// RUN_TEST(test_);

	return UNITY_END();
}