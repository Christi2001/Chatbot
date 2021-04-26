#ifndef REPLY_GUARD__H
#define REPLY_GUARD__H

#include "appointments.h"

/**
 * Prints an introduction.
 */
char* say_introduction();

// /**
//  * Print a greeting with the user's name.
//  * 
//  * @param name The user's name
//  */
// void say_hello(char* name);

/**
 * Ask the user if they have other questions.
 */
char* ask_for_other_questions();

/**
 * Tell the user (in a number of ways) that I can't process the input.
 * 
 * @return String with the reply
 */
char* say_didnt_understand();

/**
 * Shows the usual schedule of a doctor on a particular weekday.
 * 
 * @param doctor Doctor whose schedule will be showed
 * @param weekday A weekday within the schedule
 * @return String with the reply
 */
char* show_schedule(char* doctor, char* weekday);

/**
 * Shows the schedule of a doctor on a particular date (only available 
 * spots) or if the doctor is unavailable on that date, it gives the 
 * first date after when the doctor is available, along with the respective schedule.
 * 
 * @param doctor Doctor whose schedule will be showed
 * @param date Date to be checked
 * @return String with the reply
 */
char* show_modified_schedule_on_date(char* doctor, char* date);

/**
 * Lists all doctors from each department within the clinic.
 * 
 * @return String with the reply
 */
char* list_all_doctors();

/**
 * Lists all departments within the clinic.
 * 
 * @return String with the reply
 */
char* list_departments();

/**
 * Searches for a department and lists the three doctors in it.
 * 
 * @param dep The department to be searched for
 * @return String with the reply
 */
char* list_doctors_in_dep(char* dep);

/**
 * Prints the reply and hands it to chatlog() to save it.
 * 
 * @param reply The reply to be printed
 */
void respond(char* reply);

#endif