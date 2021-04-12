#ifndef REPLY_GUARD__H
#define REPLY_GUARD__H

#include "appointments.h"

/**
 * Print some introductory sentences.
 */
char* say_introduction();

/**
 * Print a greeting with the user's name.
 * 
 * @param name The user's name
 */
void say_hello(char* name);

/**
 * Print a goodbye.
 */
void say_goodbye();

/**
 * Request details about the appointment based on which of them have not been found out yet.
 * 
 * @param appointment The appointment struct containing all the details about the current appointment
 */
void ask_appointment_details(Appointment appointment);

/**
 * Ask the user if they have other questions.
 */
void ask_for_other_questions();

/**
 * Tell the user that I can't process the input.
 */
void didnt_understand();


#endif