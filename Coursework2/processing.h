#ifndef PROCESSING_GUARD__H
#define PROCESSING_GUARD__H

#include <time.h>
#include "appointments.h"

#define SEC_IN_DAY 86400

char words[100][20];
Appointment current_appointment;
char unconfirmed_doc_name[30];
char unconfirmed_dep[20];
char temp_doc_name[30];
char temp_dep[20];
char temp_date[11];
char temp_time[6];
time_t temp_sec;
char docs_in_dep[3][30];

/**
 * Takes a string as input and saves it in chatlog.txt. Then it turns it to lowercase 
 * and processes it to get rid of any characters other than letters, digits or spaces.
 * 
 * @param string The string that will be saved and converted
 * @return String containing lowercase space-separated strings of characters
 */
char* process_input(char* string);

/**
 * Takes a processed string as input and separates it into an array of words, 
 * then saves it into the "words" array.
 * 
 * @param string The string that will be separated
 * @return the array's length
 */
int split_string(char* string);

/**
 * Compares a department with every deparment in the "department" array 
 * and if found, saves it in "current_appointment" struct.
 * 
 * @param dep The department that will be compared
 * @return 0 if it has found a department or 1 if not
 */
int search_for_department(char* dep);

/**
 * Compares a string with every doctor in the "department" array 
 * and if found, saves it in "current_appointment" struct. It can 
 * find doctors even if the two names are reversed.
 * 
 * @param f_name First name
 * @param l_name Last name
 * @return 0 if it has found a doctor or 1 if not
 */
int search_for_doctor(char* f_name, char* l_name);

/**
 * Compares a name with every doctor in the "department" array 
 * and if found, asks if it refers to the doctor.
 * 
 * @param name The name to be searched
 * @return 0 if it has found a doctor or 1 if not
 */
int search_for_doctor_by_one_name(char* name);

/**
 * Compares a string with a list of words representing intent. 
 * 
 * @param word The word to be compared
 * @return 0 if the word matches one in the list or 1 if not
 */
int search_for_intent_in_word(char* word);

/**
 * Searches a string for a phrase in a list of phrases representing intent.
 * 
 * @param string The string to be searched
 * @return 0 if it has found intent in the string or 1 if not
 */
int search_for_intent_in_string(char* string);

/**
 * Searches a string for the "?" sign and for a phrase in a list of phrases representing a question.
 * 
 * @param string The string to be searched
 * @return 0 if it contains question or 1 if not
 */
int search_for_question(char* string);

/**
 * Searches a string for a phrase in a list of phrases representing a request.
 * 
 * @param string The string to be searched
 * @return 0 if it has found a request in the string or 1 if not
 */
int search_for_request(char* string);

/**
 * Searches a string for a date in mixed format, such as "the 1st of May". 
 * If found, it saves it in a global variable (temp_date).
 * 
 * @param string The string to be searched
 * @return 0 if it has found a date in the string or 1 if not
 */
int search_for_date(char* string);

/**
 * Searches a string for a date in formats, such as: "tomorrow", 
 * "the day after tomorrow", "on Tuesday in 3 weeks", "in 5 days", 
 * or "next Friday". 
 * If found, it saves it in a global variable (temp_date).
 * 
 * @param string The string to be searched
 * @return 0 if it has found a date in the string or 1 if not
 */
int search_for_date_phrase(char* string);

/**
 * Compares a word with a numeric format of date ("01.05.2001"). 
 * If found, it saves it in a global variable (temp_date).
 * 
 * @param word The word to be compared
 * @return 0 if it has found a date in the string or 1 if not
 */
int search_for_date_numeric(char* word);

/**
 * Compares a word with a numeric format of time ("12:30"). 
 * If found, it saves it in a global variable (temp_time).
 * 
 * @param word The word to be compared
 * @return 0 if it has found a date in the string or 1 if not
 */
int search_for_time(char* word);

/**
 * Searches a string for a time in mixed format, such as: 
 * "at 12 o'clock", "half past 9", "at 11" or "at 14 and a half". 
 * If found, it saves it in a global variable (temp_time).
 * 
 * @param string The string to be searched
 * @return 0 if it has found a date in the string or 1 if not
 */
int search_for_time_phrase(char* string);

/**
 * Compares a word with "pm".
 * 
 * @param word The word to be compared
 * @return 0 if the word is "pm" or 1 if not
 */
int search_for_pm(char* word);

/**
 * Saves a string in "chatlog.txt".
 * 
 * @param string String to be saved
 * @return 0 if it successfully saved the string or 1 if not
 */
int chatlog(char* string);

#endif