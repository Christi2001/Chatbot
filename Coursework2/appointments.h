#ifndef APPOINTMENTS_GUARD__H
#define APPOINTMENTS_GUARD__H

#define TOTAL_NUM_DEP 10
#define NUM_DOCS_IN_ONE_DEP 3
#define NUM_WORKDAYS_IN_SCHEDULE_PER_WEEK 3
#define MAX_NUM_APP 1000

typedef struct{
    char* weekday;
    // 8 am to 8 pm divided in 15 minute appointments (12h/30m = 24)
    // Each 30min piece has the value:
    // -> 0 if it is outside the doctor's office hours
    // -> 1 if it is in the doctor's schedule
    // -> 2 if it has an appointment
    char* session;
}Schedule;

typedef struct{
    char* full_name;
    char* appointment_price;
    Schedule schedule[NUM_WORKDAYS_IN_SCHEDULE_PER_WEEK];
}Doctor;

// each department has 3 doctors assigned to it
typedef struct{
    char* dep_title;
    Doctor doctors[NUM_DOCS_IN_ONE_DEP];
}Department;

typedef struct{
    char* app_ID;
    char* name;
    char* email;
    char* tel;
    char* age;
    char* department;
    char* doctor;
    char* date;
    char* weekday;
    char* time;
}Appointment;

// Array of all (10) department structs
Department department[TOTAL_NUM_DEP];

// Array of all appointments made at the clinic
Appointment appointment[MAX_NUM_APP];

// Struct used for handling schedule with appointments
Doctor current_schedule_on_week_X;

int Current_num_appointments;

/**
 * Prints the current date and finds the current weekday.
 * 
 * @return String of 3 characters representing the current weekday
 */
char* current_day();

long int string_to_sec(char* str);

/**
 * Takes a string representing a date in the format "dd.mm.yyyy" 
 * and turns it into a struct tm.
 * 
 * @param date The date string
 * @return struct tm structure containing all parameters
 */
struct tm string_to_tm(char* date);

/**
 * Takes a date, time and a doctor name and checks the 
 * appointment and department arrays to see if the session is free or not.
 * 
 * @param date The date of the appointment
 * @param time The time of the appointment
 * @param doc_name The doctor whose schedule will be checked
 * @return 0 if the appointment session is free, 1 if it is not 
 * and -1 if it is not within the doctor's schedule
 */
int check_availability(char* date, char* time, char* doc_name);

/**
 * Takes data from an appointment struct and saves it in "appointments.txt" and "doctors.txt". 
 * 
 * @param appointment An appointment struct containing all the info needed about an appointment
 * @return 0 if it successfully saved the appointment in the text files or 1 if not
 */
int save_appointment(Appointment appointment);

/**
 * Takes data from an appointment struct, searches for it in "appointments.txt" and if found, 
 * it removes the appointment (from "doctors.txt" as well).
 * 
 * @param appointment An appointment struct containing all the info needed about an appointment
 * @return 0 if it successfully canceled the appointment in the text files or 1 if not
 */
int cancel_appointment(Appointment appointment);

/**
 * Loads data from "appointments.txt" into an array of Appointment structs.
 * 
 * @return 0 if it successfully loaded the data or 1 if it failed
 */
int load_appointments();

/**
 * Loads data from "doctors.txt" into an array of Department structs with all the doctors.
 * 
 * @return 0 if it successfully loaded the data or 1 if it failed
 */
int load_doctors();

#endif