#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "processing.h"

char* process_input(char* string)
{
    // Save conversation in a txt file
    char* logged = (char*) malloc(210 * sizeof(char));
    strcpy(logged, "Patient: ");
    strcat(logged, string);
    strcat(logged, "\n\n");
    chatlog(logged);
    free(logged);

    char* processed_input = (char*) malloc(200 * sizeof(char));
    int j = 0;
    for(int i = 0; i < strlen(string); i++)
    {
        if(isdigit(string[i]) || isalpha(string[i]) || string[i] == ' ')
        {
            processed_input[j] = tolower(string[i]);
            j++;
        }
    }
    processed_input[j] = '\0';
    return processed_input;
}

int split_string(char* string)
{
    int k = 0;
    int j = 0;
    for(int i = 0; i <= strlen(string); i++)
    {
        if(string[i] == ' ' || string[i] == '\0')
        {
            words[k][j] = '\0';
            k++;
            j = 0;
        }
        else
        {
            words[k][j] = string[i];
            j++;
        }
    }
    return k;
}

int search_for_department(char* dep)
{
    char dep1[20] = "";
    for(int j = 0; j < strlen(dep); j++)
        dep1[j] = tolower(dep[j]);
    dep1[0] = toupper(dep[0]);
    for(int i = 0; i < TOTAL_NUM_DEP; i++)
        if(strcmp(dep1, department[i].dep_title) == 0)
        {
            strcpy(current_appointment.department, dep1);
            for(int j = 0; j < NUM_DOCS_IN_ONE_DEP; j++)
                strcpy(docs_in_dep[j], department[i].doctors[j].full_name);
            return 0;
        }
    return 1;
}

int search_for_doctor(char* f_name, char* l_name)
{
    char f_name1[20] = "";
    for(int j = 0; j < strlen(f_name); j++)
        f_name1[j] = tolower(f_name[j]);
    f_name1[0] = toupper(f_name[0]);

    char l_name1[20] = "";
    for(int j = 0; j < strlen(l_name); j++)
        l_name1[j] = tolower(l_name[j]);
    l_name1[0] = toupper(l_name[0]);

    char full_name1[30];
    full_name1[0] = '\0';
    strcat(full_name1, f_name1);
    strcat(full_name1, " ");
    strcat(full_name1, l_name1);
    char full_name2[30];
    full_name2[0] = '\0';
    strcat(full_name2, l_name1);
    strcat(full_name2, " ");
    strcat(full_name2, f_name1);
    for(int i = 0; i < TOTAL_NUM_DEP; i++)
        for(int j = 0; j < NUM_DOCS_IN_ONE_DEP; j++)
        {
            if(strcmp(full_name1, department[i].doctors[j].full_name) == 0)
            {
                strcpy(temp_doc_name, full_name1);
                strcpy(temp_dep, department[i].dep_title);
                return 0;
            }
            else if(strcmp(full_name2, department[i].doctors[j].full_name) == 0)
            {
                strcpy(temp_doc_name, full_name2);
                strcpy(temp_dep, department[i].dep_title);
                return 0;
            }
        }
    return 1;
}

int search_for_doctor_by_one_name(char* name)
{
    int m;
    int n;
    char name1[20] = "";
    for(int i = 0; i < strlen(name); i++)
        name1[i] = tolower(name[i]);
    name1[0] = toupper(name[0]);
    char names[2][15];
    for(int i = 0; i < TOTAL_NUM_DEP; i++)
        for(int j = 0; j < NUM_DOCS_IN_ONE_DEP; j++)
        {
            m = 0;
            n = 0;
            for(int l = 0; l <= strlen(department[i].doctors[j].full_name); l++)
            {
                if(department[i].doctors[j].full_name[l] == ' ' || department[i].doctors[j].full_name[l] == '\0')
                {
                    names[m][n] = '\0';
                    m++;
                    n = 0;
                }
                else
                {
                    names[m][n] = department[i].doctors[j].full_name[l];
                    n++;
                }
            }
            if(strcmp(name1, names[0]) == 0 || strcmp(name1, names[1]) == 0)
            {
                strcpy(unconfirmed_doc_name, department[i].doctors[j].full_name);
                strcpy(unconfirmed_dep, department[i].dep_title);
                return 0;
            }
            for(int b = 0; b < 15; b++)
            {
                names[0][b] = '\0';
                names[1][b] = '\0';
            }
        }
    return 1;
}

int search_for_intent_in_word(char* word)
{
    char* intention[8] = {"want", "wish", "must", "need", "may", "should", "shall", "can"};
    for(int i = 0; i < 8; i++)
        if(strcmp(intention[i], word) == 0)
            return 0;
    return 1;
}

int search_for_intent_in_string(char* string)
{
    char* ptr = NULL;
    char* intention[3] = {" would like ", " wish for ", " would love "};
    for(int i = 0; i < 3; i++)
    {
        ptr = strstr(string, intention[i]);
        if(ptr != NULL)
            return 0;
    }
    return 1;
}

int search_for_question(char* string)
{
    if(string[strlen(string) - 1] == '?')
    {
        char* ptr = NULL;
        char* request[12] = {"Who ", "What ", "Which ", "Where ", "How ", "When ", " who ", " what ", " which ", " where ", " how ", " when "};
        for(int i = 0; i < 12; i++)
        {
            ptr = strstr(string, request[i]);
            if(ptr != NULL)
            {
                return 0;
            }
        }
    }
    return 1;
}

int search_for_request(char* string)
{
    char* ptr = NULL;
    char* request[10] = {" show me ", " tell me ", " may I see ", " can I see ", " can I have ", "Show me ", "Tell me ", "May I see ", "Can I see ", "Can I have "};
    for(int i = 0; i < 10; i++)
    {
        ptr = strstr(string, request[i]);
        if(ptr != NULL)
            return 0;
    }
    return 1;
}

int search_for_date(char* string)
{
    char* lower_string = (char*) malloc(200*sizeof(char));
    for(int i = 0; i < strlen(string); i++)
        lower_string[i] = tolower(string[i]);
    char* ptr1 = NULL;
    char* ptr2 = NULL;
    char* ptr3 = NULL;
    char* ptr4 = NULL;
    char* month_day[31][3] = {{"1","1st","first"},{"2","2nd","second"},{"3","3rd","third"},
    {"4","4th","fourth"},{"5","5th","fifth"},{"6","6th","sixth"},{"7","7th","seventh"},
    {"8","8th","eighth"},{"9","9th","ninth"},{"10","10th","tenth"},{"11","11th","eleventh"},
    {"12","12th","twelfth"},{"13","13th","thirteenth"},{"14","14th","fourteenth"},
    {"15","15th","fifteenth"},{"16","16th","sixteenth"},{"17","17th","seventeenth"},
    {"18","18th","eighteenth"},{"19","19th","nineteenth"},{"20","20th","twentieth"},
    {"21","21st","twenty-first"},{"22","22nd","twenty-second"},{"23","23rd","twenty-third"},
    {"24","24th","twenty-fourth"},{"25","25th","twenty-fifth"},{"26","26th","twenty-sixth"},
    {"27","27th","twenty-seventh"},{"28","28th","twenty-eighth"},{"29","29th","twenty-ninth"},
    {"30","30th","thirtieth"},{"31","31st","thirty-first"}};
    char* month[12][2] = {{"january", "jan"}, {"february", "feb"}, {"march", "mar"}, {"april", "apr"},
    {"may", "may"}, {"june", "jun"}, {"july", "jul"}, {"august", "aug"}, {"september", "sep"},
    {"october", "oct"}, {"november", "nov"}, {"december", "dec"}};
    
    char year[5];
    char date1[50];
    char date2[50];
    char date3[50];
    char date4[50];
    struct tm today = current_day();
    struct tm tdate;
    for(int i = 30; i >= 0; i--)
        for(int j = 0; j < 3; j++)
        {
            ptr1 = strstr(lower_string, month_day[i][j]);
            if(ptr1 != NULL)
            {
                for(int a = 0; a < 12; a++)
                    for(int b = 0; b < 2; b++)
                    {
                        ptr2 = strstr(lower_string, month[a][b]);
                        if(ptr2 != NULL)
                        {
                            sprintf(date1, "the %s of %s", month_day[i][j], month[a][b]);
                            ptr1 = strstr(lower_string, date1);
                            sprintf(date2, "%s of %s", month_day[i][j], month[a][b]);
                            ptr2 = strstr(lower_string, date2);
                            sprintf(date3, "%s %s", month_day[i][j], month[a][b]);
                            ptr3 = strstr(lower_string, date3);
                            sprintf(date4, "%s %s", month[a][b], month_day[i][j]);
                            ptr4 = strstr(lower_string, date4);
                            if(ptr1 != NULL || ptr2 != NULL || ptr3 != NULL || ptr4 != NULL)
                            {
                                memset(&tdate, 0, sizeof(tdate));
                                tdate.tm_mday = i + 1;
                                tdate.tm_mon = a;
                                tdate.tm_year = today.tm_year;
                                if(tdate.tm_mon < today.tm_mon)
                                    tdate.tm_year += 1;
                                else if(tdate.tm_mon == today.tm_mon)
                                    if(tdate.tm_mday < today.tm_mday)
                                        tdate.tm_year += 1;
                                strftime(temp_date, 11, "%d.%m.%Y", &tdate);
                                return 0;
                            }
                        }
                    }
            }
        }
    return 1;
}

int search_for_date_phrase(char* string)
{
    char* lower_string = (char*) malloc(200*sizeof(char));
    for(int i = 0; i < strlen(string); i++)
        lower_string[i] = tolower(string[i]);
    char* weekdays[7] = {"sunday", "monday", "tuesday", "wednesday", "thursday", "friday", "saturday"};
    struct tm today = current_day();
    time_t today_sec = mktime(&today);
    struct tm tdate;
    time_t tdate_sec = today_sec;
    char date1[20];
    char date2[20];
    char date3[20];
    char date6[20];
    char date_num[11];
    char* ptr1 = NULL;
    char* ptr2 = NULL;
    char* ptr3 = NULL;
    char* wd = NULL; // weekday for case 3
    char* ptr4 = NULL;
    char* ptr5 = NULL;
    char* ptr6 = NULL;
    
    // Case 1
    ptr1 = strstr(lower_string, "the day after tomorrow");
    if(ptr1 != NULL)
    {
        tdate_sec = today_sec + 2*SEC_IN_DAY;
        tdate = *localtime(&tdate_sec);
        strftime(temp_date, 11, "%d.%m.%Y", &tdate);
        return 0;
    }

    // Case 2
    ptr2 = strstr(lower_string, "tomorrow");
    if(ptr2 != NULL)
    {
        tdate_sec = today_sec + SEC_IN_DAY;
        tdate = *localtime(&tdate_sec);
        strftime(temp_date, 11, "%d.%m.%Y", &tdate);
        return 0;
    }
    
    // Case 3
    for(int i = 1; i <= 16; i++)
    {
        sprintf(date3, "in %i weeks", i);
        ptr3 = strstr(lower_string, date3);
        if(ptr3 != NULL)
        {
            // bring working date (tdate) to sunday the week before
            if(today.tm_wday > 0)
                tdate_sec = today_sec - today.tm_wday*SEC_IN_DAY;
            tdate_sec += (7*i)*SEC_IN_DAY;
            for(int j = 0; j < 7; j++)
            {
                wd = strstr(lower_string, weekdays[j]);
                if(wd != NULL)
                {
                    if(j == 0)
                        tdate_sec += 7*SEC_IN_DAY;
                    else
                        tdate_sec += j*SEC_IN_DAY;
                    tdate = *localtime(&tdate_sec);
                    strftime(temp_date, 11, "%d.%m.%Y", &tdate);
                    return 0;
                }
            }
            temp_sec = tdate_sec;
            return -1;
        }
    }

    // Case 4
    ptr4 = strstr(lower_string, "next ");
    ptr5 = strstr(lower_string, "in a week");
    if(ptr4 != NULL || ptr5 != NULL)
    {
        if(today.tm_wday > 0)
            tdate_sec = today_sec - today.tm_wday*SEC_IN_DAY;
        tdate_sec += 7*SEC_IN_DAY;
        for(int j = 0; j < 7; j++)
        {
            wd = strstr(lower_string, weekdays[j]);
            if(wd != NULL)
            {
                tdate_sec += j*SEC_IN_DAY;
                tdate = *localtime(&tdate_sec);
                strftime(temp_date, 11, "%d.%m.%Y", &tdate);
                return 0;
            }
        }
        temp_sec = tdate_sec;
        return -1;
    }
    
    // Case 5
    for(int i = 0; i < 31; i++)
    {
        sprintf(date6, "in %i days", i);
        ptr6 = strstr(lower_string, date6);
        if(ptr6 != NULL)
        {
            tdate_sec = today_sec + i*SEC_IN_DAY;
            tdate = *localtime(&tdate_sec);
            strftime(temp_date, 11, "%d.%m.%Y", &tdate);
            return 0;
        }
    }
    return 1;
}

int search_for_date_numeric(char* word)
{
    // 12.05.2021
    // 5.12.2020
    // 5.5.2021
    // 15.5.2020
    // 12/05/21
    // 5/5/21
    // 5.5.21
    // 5-5-21
    char date[11];
    char str[3][5];
    int k = 0;
    int j = 0;
    if((strlen(word) >= 6 && strlen(word) <=11) &&
    ((word[1] == '.' || word[1] == '-' || word[1] == '/') || (word[2] == '.' || word[2] == '-' || word[2] == '/')) && 
    ((word[3] == '.' || word[3] == '-' || word[3] == '/') || (word[4] == '.' || word[4] == '-' || word[4] == '/') || 
    (word[5] == '.' || word[5] == '-' || word[5] == '/')) && isdigit(word[0]) != 0)
    {
        k = 0;
        j = 0;
        for(int i = 0; i <= strlen(word); i++)
        {
            if(word[i] == '.' || word[i] == '-' || word[i] == '/' || word[i] == ' ' || word[i] == '\0')
            {
                str[k][j] = '\0';
                k++;
                j = 0;
            }
            else
            {
                str[k][j] = word[i];
                j++;
            }
        }
        strcpy(date, "");
        for(int a = 0; a < 2; a++)
        {
            if(strlen(str[a]) == 1)
                strcat(date, "0");
            strcat(date, str[a]);
            strcat(date, ".");
        }
        if(strlen(str[2]) == 2)
            strcat(date, "20");
        strcat(date, str[2]);
        strcpy(temp_date, date);
        return 0;
    }
    return 1;
}

int search_for_time(char* word)
{
    char hour[6] = "";
    if((strlen(word) >= 4 && strlen(word) <= 6) &&
    (word[1] == ':' || word[2] == ':') && isdigit(word[0]) != 0 && isdigit(word[3]) != 0)
    {
        if(word[1] == ':')
            strcpy(hour, "0");
        if(word[strlen(word) - 1] == '.')
            word[strlen(word) - 1] = '\0';
        else if(strlen(word) == 6) return 1;
        strcat(hour, word);
        strcpy(temp_time, hour);
        return 0;
    }
    return 1;
}

int search_for_time_phrase(char* string)
{
    char* lower_string = (char*) malloc(200*sizeof(char));
    for(int i = 0; i < strlen(string); i++)
        lower_string[i] = tolower(string[i]);
    char* ptr1 = NULL;
    char* ptr2 = NULL;
    char* ptr3 = NULL;
    char* ptr4 = NULL;
    char* ptr5 = NULL;
    char time[20] = "";
    char hour[6] = "";
    for(int i = 100; i >= 1; i--)
    {
        sprintf(time, "at %i", i);
        ptr1 = strstr(lower_string, time);
        if(ptr1 != NULL)
        {
            // The loop goes from 99 and if it finds invalid hours it returns 1.
            // Without this is would detect "at 25 o'clock" as valid
            // due to "at 2" being valid (for example).
            if(i > 24)
                return 1;
            ptr2 = strstr(lower_string, "and a half");
            sprintf(time, "%i", i);
            if(strlen(time) == 1)
                strcpy(hour, "0");
            strcat(hour, time);
            if(ptr2 != NULL)
                strcat(hour, ":30");
            else
                strcat(hour, ":00");
            strcpy(temp_time, hour);
            return 0;
        }
        sprintf(time, "half past %i", i);
        ptr3 = strstr(lower_string, time);
        if(ptr3 != NULL)
        {
            sprintf(time, "%i", i);
            if(strlen(time) == 1)
                strcpy(hour, "0");
            strcat(hour, time);
            strcat(hour, ":30");
            strcpy(temp_time, hour);
            return 0;
        }
    }
    return 1;
}

int search_for_pm(char* word)
{
    if(strcmp(word, "pm") == 0 || strcmp(word, "PM"))
        return 0;
    return 1;
}

int chatlog(char* string)
{
    FILE* chatlog;
    chatlog = fopen("chatlog.txt", "a");
    if(!chatlog)
    {
        printf("Cannot open file!");
        return 1;
    }
    fprintf(chatlog, "%s", string);
    fclose(chatlog);
}
