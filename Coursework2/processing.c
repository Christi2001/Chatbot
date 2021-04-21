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
        string[i] = tolower(string[i]);
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
    int m;
    int n;
    char name1[20] = "";
    for(int j = 0; j < strlen(name); j++)
        name1[j] = tolower(name[j]);
    name1[0] = toupper(name[0]);
    char names[2][15];
    for(int i = 0; i < 10; i++)
        for(int j = 0; j < 3; j++)
        {
            m = 0;
            n = 0;
            for(int l = 0; l < strlen(department[i].doctors[j].full_name); l++)
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
                strcpy(temp_doc_name, department[i].doctors[j].full_name);
                strcpy(temp_dep, department[i].dep_title);
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
    char* intention[3] = {"would like", "wish for", "would love"};
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
    char* question = NULL;
    question = strstr(string, "?");
    if(question != NULL)
    {
        char* ptr = NULL;
        char* request[10] = {"What", "Which", "Where", "How", "When", "what", "which", "where", "how", "when"};
        for(int i = 0; i < 10; i++)
        {
            ptr = strstr(string, request[i]);
            if(ptr != NULL)
                return 0;
        }
    }
    return 1;
}

int search_for_request(char* string)
{
    char* ptr = NULL;
    char* request[10] = {"show me", "tell me", "may I see", "can I see", "Can I have", "Show me", "Tell me", "May I see", "Can I see", "Can I have"};
    for(int i = 0; i < 10; i++)
    {
        ptr = strstr(string, request[i]);
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

// int main()
// {
//     current_appointment.doctor = (char*) malloc(30*sizeof(char));
// 	temp_doc_name = (char*) malloc(30*sizeof(char));
//     load_doctors();
//     int i = search_for_doctor_by_one_name("Madina");
//     printf("%i\n", i);
//     free(current_appointment.doctor);
// 	free(temp_doc_name);
// }