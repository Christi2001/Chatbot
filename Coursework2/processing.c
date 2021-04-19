#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "processing.h"

char* process_input(char* string)
{
    // Save conversation in a txt file
    char* logged = (char*) malloc(210 * sizeof(char));
    strcpy(logged, "Patient: ");
    strcat(logged, string);
    chatlog(logged);
    free(logged);

    char* processed_input = (char*) malloc(200 * sizeof(char));
    int j = 0;
    // scanf(" %[^\n]%*c", string);
    for(int i = 0; i < strlen(string); i++)
    {
        // string[i] = tolower(string[i]);
        if(isdigit(string[i]) || isalpha(string[i]) || string[i] == ' ')
        {
            processed_input[j] = string[i];
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
    for(int i = 0; i < strlen(string); i++)
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
    return k+1;
}

int search_for_department(char* dep)
{
    char dep1[20] = "";
    for(int j = 0; j < strlen(dep); j++)
        dep1[j] = tolower(dep[j]);
    dep1[0] = toupper(dep[0]);
    for(int i = 0; i < 10; i++)
        if(strcmp(dep1, department[i].dep_title) == 0)
        {
            strcpy(current_appointment.department, dep1);
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
    for(int i = 0; i < 10; i++)
        for(int j = 0; j < 3; j++)
        {
            if(strcmp(full_name1, department[i].doctors[j].full_name) == 0)
            {
                strcpy(current_appointment.doctor, full_name1);
                strcpy(current_appointment.department, department[i].dep_title);
                return 0;
            }
            else if(strcmp(full_name2, department[i].doctors[j].full_name) == 0)
            {
                strcpy(current_appointment.doctor, full_name2);
                strcpy(current_appointment.department, department[i].dep_title);
                return 0;
            }
        }
    return 1;
}

int search_for_doctor_by_one_name(char* name)
{
    char* ptr = NULL;
    for(int i = 0; i < 10; i++)
        for(int j = 0; j < 3; j++)
        {
            ptr = strstr(department[i].doctors[j].full_name, name);
            if(ptr != NULL)
            {
                strcpy(doc_full_name, department[i].doctors[j].full_name);
                return 0;
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
    char* intention[3] = {"would like", "wish for", "would love"};
    for(int i = 0; i < 3; i++)
    {
        ptr = strstr(string, intention[i]);
        if(ptr != NULL)
            return 0;
    }
    return 1;
}

int search_for_date(char* string, char* date)
{
    return 0;
}

int search_for_weekday(char* string, char* weekday)
{
    return 0;
}

int search_for_time(char* string, char* time)
{
    return 0;
}

int search_for_keyword(char* string, char* keyword)
{
    return 0;
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
    fprintf(chatlog, "%s\n", string);
    fclose(chatlog);
}
