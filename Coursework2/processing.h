#ifndef PROCESSING_GUARD__H
#define PROCESSING_GUARD__H

#include "appointments.h"
char words[100][20];
Appointment current_appointment;
char* doc_full_name;

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
 * Compares a string with every deparment in the "department" array 
 * and if found, saves it in "current_appointment" struct.
 * 
 * @param dep The string that will be compared
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
 * @return 0 if it has found a phrase in the list or 1 if not
 */
int search_for_intent_in_string(char* string);

/**
 * Searches an array of strings for any occurence of a date.
 * 
 * @param array_of_strings The array of strings that will be searched
 * @param date The date to search for
 * @return 0 if it has found a date or 1 if not
 */
int search_for_date(char* array_of_strings, char* date);

/**
 * Searches an array of strings for any occurence of a weekday.
 * 
 * @param array_of_strings The array of strings that will be searched
 * @param weekday The day of the week to search for
 * @return 0 if it has found a weekday or 1 if not
 */
int search_for_weekday(char* array_of_strings, char* weekday);

/**
 * Searches an array of strings for any occurence of time.
 * 
 * @param array_of_strings The array of strings that will be searched
 * @param time The time to search for
 * @return 0 if it has found a date or 1 if not
 */
int search_for_time(char* array_of_strings, char* time);

/**
 * Searches an array of strings for a given keyword.
 * 
 * @param array_of_strings The array of strings that will be searched
 * @param keyword A keyword that will be searched for
 * @return 0 if it has found the keyword or 1 if not
 */
int search_for_keyword(char* array_of_strings, char* keyword);

/**
 * Saves a string in "chatlog.txt".
 * 
 * @param string String to be saved
 * @return 0 if it successfully saved the string or 1 if not
 */
int chatlog(char* string);

#endif