#ifndef PROCESSING_GUARD__H
#define PROCESSING_GUARD__H

typedef struct{
    char* weekday;
    int day;
    int month;
}Date;

/**
 * Takes a string as input and saves it in chatlog.txt. Then it turns it to lowercase 
 * and processes it to get rid of any characters other than letters, digits or spaces.
 * 
 * @param string The string that will be saved and converted
 * @return String containing lowercase space-separated strings of characters
 */
char* process_input(char* string);

/**
 * Searches a string for a department from the list of departments in "department.txt".
 * 
 * @param string The string that will be searched
 * @return 1 if it has found a department or 0 if not
 */
int search_for_department(char* string);

/**
 * Searches a string for a doctor from the list of doctors in "doctor.txt".
 * 
 * @param string The string that will be searched
 * @return 1 if it has found a doctor or 0 if not
 */
int search_for_doctor(char* string);

/**
 * Searches a string for any occurence of a date.
 * 
 * @param string The string that will be searched
 * @param date The date to search for
 * @return 1 if it has found a date or 0 if not
 */
int search_for_date(char* string, char* date);

/**
 * Searches a string for any occurence of a weekday.
 * 
 * @param string The string that will be searched
 * @param weekday The day of the week to search for
 * @return 1 if it has found a weekday or 0 if not
 */
int search_for_weekday(char* string, char* weekday);

/**
 * Searches a string for any occurence of time.
 * 
 * @param string The string that will be searched
 * @param time The time to search for
 * @return 1 if it has found a date or 0 if not
 */
int search_for_time(char* string, char* time);

/**
 * Searches a string for a given keyword.
 * 
 * @param string The string that will be searched
 * @param keyword A keyword that will be searched for
 * @return 1 if it has found the keyword or 0 if not
 */
int search_for_keyword(char* string, char* keyword);

#endif