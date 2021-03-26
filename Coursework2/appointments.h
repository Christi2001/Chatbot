#ifndef APPOINTMENTS_GUARD__H
#define APPOINTMENTS_GUARD__H

#define MAX_NUM_DOCTORS_IN_ONE_DEPARTMENT 10

typedef struct{
    char weekday[4];
    // 8 am to 8 pm divided in 15 minute appointments (12h/30m = 24)
    // Each 30min piece has the value:
    // -> 0 if it is outside the doctor's office hours
    // -> 1 if it is in the doctor's schedule
    // -> 2 if it has an appointment
    int schedule[24];
}Schedule;

typedef struct{
    char* full_name;
    int appointment_price;
    Schedule schedule[4][5]; // 4 weeks with 5 workdays
}Doctor;

typedef struct{
    char* dep_title;
    int num_doctors;
    Doctor doctors[MAX_NUM_DOCTORS_IN_ONE_DEPARTMENT];
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
    char* time;
}Appointment;

/**
 * Prints the current date and finds the current weekday.
 * 
 * @return String of 3 characters representing the current weekday
 */
char* current_day();

/**
 * Takes a date and time and checks the "appointments.txt" and
 * the "doctors.txt" files to see if the spot is taken or not.
 * 
 * @param date The date of the appointment
 * @param time The time of the appointment
 * @param doctor The doctor whose schedule will be checked
 * @return 1 if the date and time are not taken or 0 if they are
 */
int check_date_time(char* date, char* time, Doctor doctor);

/**
 * Takes data from an appointment struct and saves it in "appointments.txt" and "doctors.txt". 
 * 
 * @param appointment An appointment struct containing all the info needed about an appointment
 * @return 1 if it successfully saved the appointment in the text files or 0 if not
 */
int save_appointment(Appointment appointment);

/**
 * Takes data from an appointment struct, searches for it in "appointments.txt" and if found, 
 * it removes the appointment (from "doctors.txt" as well).
 * 
 * @param appointment An appointment struct containing all the info needed about an appointment
 * @return 1 if it successfully canceled the appointment in the text files or 0 if not
 */
int cancel_appointment(Appointment appointment);

/**
 * Loads data from "appointments.txt" into an array of Appointment structs.
 * 
 * @return 1 if it successfully loaded the data or 0 if it failed
 */
int load_appointments();

/**
 * Loads data from "doctors.txt" into an array of Doctor structs.
 * 
 * @return 1 if it successfully loaded the data or 0 if it failed
 */
int load_doctors();

#endif