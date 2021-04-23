#include <stdlib.h>
#include <time.h>

#include "unity.h"
#include "processing.h"
#include "appointments.h"
#include "replies.h"

//---------------------------------------------------------------------------------------
// Appointments Module
//---------------------------------------------------------------------------------------

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
	
	int free1 = check_availability("16.04.2021", "09:00", "Kelsie Martinez");
	int busy1 = check_availability("16.04.2021", "09:30", "Kelsie Martinez");
	int outside_sch1 = check_availability("16.04.2021", "13:00", "Kelsie Martinez");
	int free2 = check_availability("08.04.2021", "16:30", "Mohamed Webster");
	int busy2 = check_availability("06.04.2021", "13:30", "Mohamed Webster");
	int outside_sch2 = check_availability("07.04.2021", "12:00", "Mohamed Webster");

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
	TEST_ASSERT_EQUAL_STRING("Otolaryngology", appointment[5].department);
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
	TEST_ASSERT_EQUAL_STRING("Orthopedy", department[0].dep_title);
	TEST_ASSERT_EQUAL_STRING("Zaara Rosales", department[0].doctors[0].full_name);
	TEST_ASSERT_EQUAL_STRING("70", department[0].doctors[0].appointment_price);
	TEST_ASSERT_EQUAL_STRING("Mon", department[0].doctors[0].schedule[0].weekday);
	
	TEST_ASSERT_EQUAL_STRING("85", department[9].doctors[2].appointment_price);
	TEST_ASSERT_EQUAL_STRING("000011110000111111110000", department[9].doctors[2].schedule[2].session);
	//Random Tests
	TEST_ASSERT_EQUAL_STRING("Dermatology", department[3].dep_title);
	TEST_ASSERT_EQUAL_STRING("Francesco Blackwell", department[3].doctors[2].full_name);
	TEST_ASSERT_EQUAL_STRING("70", department[3].doctors[0].appointment_price);
	TEST_ASSERT_EQUAL_STRING("Alicja Osborn", department[4].doctors[0].full_name);
	TEST_ASSERT_EQUAL_STRING("Mon", department[4].doctors[0].schedule[0].weekday);
	TEST_ASSERT_EQUAL_STRING("Thu", department[4].doctors[1].schedule[1].weekday);
	TEST_ASSERT_EQUAL_STRING("000011110000111111110000", department[4].doctors[1].schedule[1].session);
}

//---------------------------------------------------------------------------------------
// Processing Module
//---------------------------------------------------------------------------------------

void test_search_for_department() {
	current_appointment.department = (char*) malloc(20*sizeof(char));
	// TEST_ASSERT_EQUAL_INT(0, search_for_department("endocrinology"));
	TEST_ASSERT_EQUAL_INT(0, search_for_department("Endocrinology"));
	TEST_ASSERT_EQUAL_INT(0, search_for_department("ENDOCRINOLOGY"));
	TEST_ASSERT_EQUAL_INT(0, search_for_department("orthopedy"));
	TEST_ASSERT_EQUAL_INT(0, search_for_department("neurology"));
	TEST_ASSERT_EQUAL_INT(1, search_for_department("torthopedy"));
	TEST_ASSERT_EQUAL_INT(1, search_for_department("orthopeyd"));
	TEST_ASSERT_EQUAL_INT(1, search_for_department("orthope"));
	
	free(current_appointment.department);
}

void test_search_for_doctor() {
	current_appointment.doctor = (char*) malloc(30*sizeof(char));
	TEST_ASSERT_EQUAL_INT(0, search_for_doctor("Colleen", "Wall"));
	TEST_ASSERT_EQUAL_INT(0, search_for_doctor("Wall", "Colleen"));
	TEST_ASSERT_EQUAL_INT(1, search_for_doctor("Colleen", "Walls"));
	TEST_ASSERT_EQUAL_INT(1, search_for_doctor("tColleen", "LWall"));
	TEST_ASSERT_EQUAL_INT(1, search_for_doctor("Colleen", "Colleen"));
	TEST_ASSERT_EQUAL_INT(1, search_for_doctor("Wall", "Wall"));
	TEST_ASSERT_EQUAL_INT(0, search_for_doctor("Mohamed", "Webster"));
	TEST_ASSERT_EQUAL_INT(0, search_for_doctor("Farmer", "Derek"));
	free(current_appointment.doctor);
}

void test_search_for_doctor_by_one_name() {
	current_appointment.doctor = (char*) malloc(30*sizeof(char));
	temp_doc_name = (char*) malloc(30*sizeof(char));
	temp_dep = (char*) malloc(20*sizeof(char));
	TEST_ASSERT_EQUAL_INT(0, search_for_doctor_by_one_name("Colleen"));
	TEST_ASSERT_EQUAL_INT(0, search_for_doctor_by_one_name("Wall"));
	TEST_ASSERT_EQUAL_INT(0, search_for_doctor_by_one_name("Isaac"));
	TEST_ASSERT_EQUAL_INT(1, search_for_doctor_by_one_name("Walls"));
	TEST_ASSERT_EQUAL_INT(1, search_for_doctor_by_one_name("Moham"));
	TEST_ASSERT_EQUAL_INT(1, search_for_doctor_by_one_name("afsdaf"));
	TEST_ASSERT_EQUAL_INT(1, search_for_doctor_by_one_name("Hello"));
	free(current_appointment.doctor);
	free(temp_doc_name);
	free(temp_dep);

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

void test_search_for_question() {
	TEST_ASSERT_EQUAL_INT(0, search_for_question("Which doctors are working at Neurology?"));
	TEST_ASSERT_EQUAL_INT(0, search_for_question("When is dr. Webster free?"));
	TEST_ASSERT_EQUAL_INT(0, search_for_question("Ok, when is dr. Webster free?"));
	TEST_ASSERT_EQUAL_INT(0, search_for_question("Hello, which doctors are working at Cardiology?"));
	TEST_ASSERT_EQUAL_INT(1, search_for_question("I want to make an appointment?"));
	TEST_ASSERT_EQUAL_INT(1, search_for_question("Can I make an appointment."));
}

void test_search_for_request() {
	TEST_ASSERT_EQUAL_INT(0, search_for_request("Can I see the services you provide?"));
	TEST_ASSERT_EQUAL_INT(0, search_for_request("Please show me a list of the doctors working here."));
	TEST_ASSERT_EQUAL_INT(0, search_for_request("Can I have the services you provide?"));
	TEST_ASSERT_EQUAL_INT(1, search_for_request("Me show the services you provide."));
	TEST_ASSERT_EQUAL_INT(1, search_for_request("Can I seefsd the services you provide?"));
}

void test_search_for_date() {
	temp_date = (char*) malloc(11*sizeof(char));
	TEST_ASSERT_EQUAL_INT(0, search_for_date("1st may"));
	TEST_ASSERT_EQUAL_STRING("01.05.2021", temp_date);
	TEST_ASSERT_EQUAL_INT(0, search_for_date("january 1st"));
	TEST_ASSERT_EQUAL_STRING("01.01.2022", temp_date);
	TEST_ASSERT_EQUAL_INT(0, search_for_date("31st December"));
	TEST_ASSERT_EQUAL_STRING("31.12.2021", temp_date);
	TEST_ASSERT_EQUAL_INT(0, search_for_date("23rd of January"));
	TEST_ASSERT_EQUAL_STRING("23.01.2022", temp_date);
	TEST_ASSERT_EQUAL_INT(0, search_for_date("on the Twenty-second of March"));
	TEST_ASSERT_EQUAL_STRING("22.03.2022", temp_date);
	TEST_ASSERT_EQUAL_INT(0, search_for_date("May first"));
	TEST_ASSERT_EQUAL_STRING("01.05.2021", temp_date);
	TEST_ASSERT_EQUAL_INT(0, search_for_date("june 3"));
	TEST_ASSERT_EQUAL_STRING("03.06.2021", temp_date);
	free(temp_date);
}

void test_search_for_date_phrase() {
	temp_date = (char*) malloc(11*sizeof(char));
	struct tm today = current_day();
    time_t today_sec = mktime(&today);
	time_t t_sec;
	struct tm today_plus;
	char today_date[11];

	TEST_ASSERT_EQUAL_INT(0, search_for_date_phrase("I want an appointment Tomorrow"));
	time_t tomorrow = today_sec + 1*SEC_IN_DAY;
	today_plus = *localtime(&tomorrow);
	strftime(today_date, 11, "%d.%m.%Y", &today_plus);
	TEST_ASSERT_EQUAL_STRING(today_date, temp_date);
	
	TEST_ASSERT_EQUAL_INT(0, search_for_date_phrase("Can I come the day after tomorrow"));
	tomorrow = today_sec + 2*SEC_IN_DAY;
	today_plus = *localtime(&tomorrow);
	strftime(today_date, 11, "%d.%m.%Y", &today_plus);
	TEST_ASSERT_EQUAL_STRING(today_date, temp_date);

	TEST_ASSERT_EQUAL_INT(0, search_for_date_phrase("I would like to come in 3 days"));
	tomorrow = today_sec + 3*SEC_IN_DAY;
	today_plus = *localtime(&tomorrow);
	strftime(today_date, 11, "%d.%m.%Y", &today_plus);
	TEST_ASSERT_EQUAL_STRING(today_date, temp_date);
	
	if(today.tm_wday > 0)
        today_sec = today_sec - today.tm_wday*SEC_IN_DAY;
	t_sec = today_sec;

	TEST_ASSERT_EQUAL_INT(0, search_for_date_phrase("I want an appointment on tuesday in 2 weeks."));
	today_sec = t_sec + (2*7+2)*SEC_IN_DAY;
	today_plus = *localtime(&today_sec);
	strftime(today_date, 11, "%d.%m.%Y", &today_plus);
	TEST_ASSERT_EQUAL_STRING(today_date, temp_date);

	TEST_ASSERT_EQUAL_INT(0, search_for_date_phrase("In 4 weeks on Sunday"));
	today_sec = mktime(&today);
	today_sec = t_sec + (4*7+7)*SEC_IN_DAY;
	today_plus = *localtime(&today_sec);
	strftime(today_date, 11, "%d.%m.%Y", &today_plus);
	TEST_ASSERT_EQUAL_STRING(today_date, temp_date);
	
	TEST_ASSERT_EQUAL_INT(0, search_for_date_phrase("in 3 weeks saturday"));
	today_sec = t_sec + (3*7+6)*SEC_IN_DAY;
	today_plus = *localtime(&today_sec);
	strftime(today_date, 11, "%d.%m.%Y", &today_plus);
	TEST_ASSERT_EQUAL_STRING(today_date, temp_date);
	
	TEST_ASSERT_EQUAL_INT(0, search_for_date_phrase("next tuesday"));
	today_sec = t_sec + (7+2)*SEC_IN_DAY;
	today_plus = *localtime(&today_sec);
	strftime(today_date, 11, "%d.%m.%Y", &today_plus);
	TEST_ASSERT_EQUAL_STRING(today_date, temp_date);

	TEST_ASSERT_EQUAL_INT(0, search_for_date_phrase("Next week on Friday"));
	today_sec = t_sec + (7+5)*SEC_IN_DAY;
	today_plus = *localtime(&today_sec);
	strftime(today_date, 11, "%d.%m.%Y", &today_plus);
	TEST_ASSERT_EQUAL_STRING(today_date, temp_date);

	free(temp_date);
}

void test_search_for_date_numeric() {
	temp_date = (char*) malloc(11*sizeof(char));
	TEST_ASSERT_EQUAL_INT(0, search_for_date_numeric("12.03.2021"));
	TEST_ASSERT_EQUAL_STRING("12.03.2021", temp_date);
	TEST_ASSERT_EQUAL_INT(0, search_for_date_numeric("12-03-2021"));
	TEST_ASSERT_EQUAL_STRING("12.03.2021", temp_date);
	TEST_ASSERT_EQUAL_INT(0, search_for_date_numeric("12/03/2021"));
	TEST_ASSERT_EQUAL_STRING("12.03.2021", temp_date);
	TEST_ASSERT_EQUAL_INT(0, search_for_date_numeric("12.03.21"));
	TEST_ASSERT_EQUAL_STRING("12.03.2021", temp_date);
	TEST_ASSERT_EQUAL_INT(0, search_for_date_numeric("12-03-21"));
	TEST_ASSERT_EQUAL_STRING("12.03.2021", temp_date);
	TEST_ASSERT_EQUAL_INT(0, search_for_date_numeric("12/03/21"));
	TEST_ASSERT_EQUAL_STRING("12.03.2021", temp_date);
	TEST_ASSERT_EQUAL_INT(0, search_for_date_numeric("1.3.2021"));
	TEST_ASSERT_EQUAL_STRING("01.03.2021", temp_date);
	TEST_ASSERT_EQUAL_INT(0, search_for_date_numeric("1.12.2021"));
	TEST_ASSERT_EQUAL_STRING("01.12.2021", temp_date);
	TEST_ASSERT_EQUAL_INT(0, search_for_date_numeric("12/3/2021"));
	TEST_ASSERT_EQUAL_STRING("12.03.2021", temp_date);
	TEST_ASSERT_EQUAL_INT(0, search_for_date_numeric("1-3-21"));
	TEST_ASSERT_EQUAL_STRING("01.03.2021", temp_date);
	TEST_ASSERT_EQUAL_INT(1, search_for_date_numeric("12032021"));
	TEST_ASSERT_EQUAL_INT(1, search_for_date_numeric("1321"));
	TEST_ASSERT_EQUAL_INT(1, search_for_date_numeric("1.3.2"));
	TEST_ASSERT_EQUAL_INT(1, search_for_date_numeric("ab.cd.efgh"));
	free(temp_date);
}

void test_search_for_time() {
	temp_time = (char*) malloc(6*sizeof(char));
	TEST_ASSERT_EQUAL_INT(0, search_for_time("15:30"));
	TEST_ASSERT_EQUAL_STRING("15:30", temp_time);
	TEST_ASSERT_EQUAL_INT(0, search_for_time("6:00"));
	TEST_ASSERT_EQUAL_STRING("06:00", temp_time);
	TEST_ASSERT_EQUAL_INT(1, search_for_time("126:00"));
	TEST_ASSERT_EQUAL_INT(1, search_for_time("07:000"));
	free(temp_time);
}

void test_search_for_time_phrase() {
	temp_time = (char*) malloc(6*sizeof(char));
	TEST_ASSERT_EQUAL_INT(0, search_for_time_phrase("tomorrow at 9"));
	TEST_ASSERT_EQUAL_STRING("09:00", temp_time);
	TEST_ASSERT_EQUAL_INT(0, search_for_time_phrase("Can I come at 12?"));
	TEST_ASSERT_EQUAL_STRING("12:00", temp_time);
	TEST_ASSERT_EQUAL_INT(0, search_for_time_phrase("I'm going to be there at 8 o'clock"));
	TEST_ASSERT_EQUAL_STRING("08:00", temp_time);
	TEST_ASSERT_EQUAL_INT(0, search_for_time_phrase("At 16 o'clock!"));
	TEST_ASSERT_EQUAL_STRING("16:00", temp_time);
	TEST_ASSERT_EQUAL_INT(0, search_for_time_phrase("At 15 and a half"));
	TEST_ASSERT_EQUAL_STRING("15:30", temp_time);
	TEST_ASSERT_EQUAL_INT(0, search_for_time_phrase("Can I come at half past 11?"));
	TEST_ASSERT_EQUAL_STRING("11:30", temp_time);
	TEST_ASSERT_EQUAL_INT(0, search_for_time_phrase("Can I come at half past 19?"));
	TEST_ASSERT_EQUAL_STRING("19:30", temp_time);
	TEST_ASSERT_EQUAL_INT(1, search_for_time_phrase("I can come at 25 o'clock"));
	free(temp_time);
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
	RUN_TEST(test_string_to_sec);
	RUN_TEST(test_string_to_tm);
	// RUN_TEST(test_check_availability);
	RUN_TEST(test_load_doctors);
	RUN_TEST(test_load_appointments);
	//Processing Module
	RUN_TEST(test_search_for_department);
	RUN_TEST(test_search_for_doctor);
	RUN_TEST(test_search_for_doctor_by_one_name);
	RUN_TEST(test_search_for_intent_in_word);
	RUN_TEST(test_search_for_intent_in_string);
	RUN_TEST(test_search_for_question);
	RUN_TEST(test_search_for_request);
	RUN_TEST(test_search_for_date);
	RUN_TEST(test_search_for_date_phrase);
	RUN_TEST(test_search_for_date_numeric);
	RUN_TEST(test_search_for_time);
	RUN_TEST(test_search_for_time_phrase);

	return UNITY_END();
}