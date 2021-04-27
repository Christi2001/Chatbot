#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "replies.h"
#include "processing.h"
#include "appointments.h"

char* say_introduction()
{
    char* string = (char*) malloc(1000*sizeof(char));
    strcpy(string, "***********************************************************************************************\n");
    strcat(string, "**                                A    L    B    E    R    T                                 **\n");
    strcat(string, "***********************************************************************************************\n");
    printf("%s", string);
    chatlog(string);
    strcpy(string, "Hello! My name is Albert and I am your virtual assistant at this clinic.\nHow may I help you?\n");
    return string;
}

// void say_hello_name(char* name)
// {
//     // printf("");
// }

char* ask_for_other_questions()
{
    char* string = (char*) malloc(100*sizeof(char));
    srand(time(0));
    int random = rand() % 3;
    char response[3][100] = {"Do you have any other questions?\n", "Can I help you with anything else?\n",
    "Do you need help with anything else?\n"};
    strcpy(string, response[random]);
    return string;
}

char* say_didnt_understand()
{
    char* string = (char*) malloc(100*sizeof(char));
    srand(time(0));
    int random = rand() % 4;
    char response[4][100] = {"I'm sorry, I didn't understand that!\n", "Sorry, I didn't quite catch that...\n",
    "Hmm, I'm not sure...\n", "I am unsure of what you meant by that...\n"};
    strcpy(string, response[random]);
    return string;
}

char* show_price(char* doctor)
{
    char* string = (char*) malloc(1000*sizeof(char));
    for(int i = 0; i < TOTAL_NUM_DEP; i++)
        for(int j = 0; j < NUM_DOCS_IN_ONE_DEP; j++)
            if(strcmp(doctor, department[i].doctors[j].full_name) == 0)
            {
                sprintf(string, "The price of a consultation with dr. %s is %s GBP.\n", department[i].doctors[j].full_name, department[i].doctors[j].appointment_price);
                return string;
            }
    return NULL;
}

char* show_schedule(char* doctor, char* weekday)
{
    char* string = (char*) malloc(1000*sizeof(char));
    int d = doctor_schedule(doctor, weekday);
    if(d == 0)
    {
        sprintf(string, "Dr. %s's schedule for %s is the following:\n", doctor, weekday);
        for(int i = 0; i < 24; i++)
        {
            if(normal_schedule.session[i] == '1')
            {
                strcat(string, hours[i]);
                strcat(string, "\t");
            }
        }
        strcat(string, "\n");
    }
    return string;
}

char* show_modified_schedule_on_date(char* doctor, char* date)
{
    char new_date[11];
    char old_date[11];
    strcpy(new_date, date);
    strcpy(old_date, date);
    char* string = (char*) malloc(1000*sizeof(char));
    int d = doctor_schedule_on_date(doctor, date);
    if(d == 0)
    {
        sprintf(string, "Dr. %s is available on %s at the following hours:\n", doctor, date);
        for(int i = 0; i < 24; i++)
        {
            if(modified_schedule.session[i] == '1')
            {
                strcat(string, hours[i]);
                strcat(string, "\t");
            }
        }
        strcat(string, "\nWhat time do you prefer?\n");
    }
    while(d == 1)
    {
        time_t t_sec = string_to_sec(new_date);
        t_sec += SEC_IN_DAY;
        struct tm tm = *localtime(&t_sec);
        strftime(new_date, 11, "%d.%m.%Y", &tm);
        d = doctor_schedule_on_date(doctor, new_date);
        strcpy(temp_date, new_date);
        sprintf(string, "Dr. %s is not available on %s, but is available on %s at the following hours:\n", doctor, old_date, new_date);
        for(int i = 0; i < 24; i++)
        {
            if(modified_schedule.session[i] == '1')
            {
                strcat(string, hours[i]);
                strcat(string, "\t");
            }
        }
        strcat(string, "\nWhat time do you prefer?\n");
    }
    return string;
}

char* list_all_doctors()
{
    char* string = (char*) malloc(1000*sizeof(char));
    char* dep = (char*) malloc(25*sizeof(char));
    char* doc = (char*) malloc(35*sizeof(char));
    strcpy(string, "The doctors in our clinic are:\n");
    for(int i = 0; i < 9; i++)
    {
        strcpy(doc, department[i].doctors[0].full_name);
        strcat(string, doc);
        strcat(string, ", ");
        strcpy(doc, department[i].doctors[1].full_name);
        strcat(string, doc);
        strcat(string, " and ");
        strcpy(doc, department[i].doctors[2].full_name);
        strcat(string, doc);
        strcat(string, " for ");
        strcpy(dep, department[i].dep_title);
        strcat(string, dep);
        strcat(string, ",\n");
    }
    strcat(string, "and ");
    strcpy(doc, department[9].doctors[0].full_name);
        strcat(string, doc);
        strcat(string, ", ");
        strcpy(doc, department[9].doctors[1].full_name);
        strcat(string, doc);
        strcat(string, " and ");
        strcpy(doc, department[9].doctors[2].full_name);
        strcat(string, doc);
        strcat(string, " for ");
        strcpy(dep, department[9].dep_title);
        strcat(string, dep);
        strcat(string, ".\n");
    return string;
}

char* list_departments()
{
    char* string = (char*) malloc(200*sizeof(char));
    char* dep = (char*) malloc(25*sizeof(char));
    strcpy(string, "The departments in our clinic are:\n");
    for(int i = 0; i < 9; i++)
    {
        strcpy(dep, department[i].dep_title);
        strcat(string, dep);
        strcat(string, ",\n");
    }
    sprintf(dep, "and %s.\n", department[9].dep_title);
    strcat(string, dep);
    return string;
}

char* list_doctors_in_dep(char* dep)
{
    char* string = (char*) malloc(200*sizeof(char));
    for(int i = 0; i < TOTAL_NUM_DEP; i++)
        if(strcmp(dep, department[i].dep_title) == 0)
        {
            sprintf(string, "The doctors working at the %s department are: dr. %s, dr. %s and dr. %s.\nWhich one would you like to make an appointment for?\n", department[i].dep_title, department[i].doctors[0].full_name, department[i].doctors[1].full_name, department[i].doctors[2].full_name);
            return string;
        }
    return NULL;
}

void respond(char* reply)
{
    printf("%s", reply);
    char* logged = (char*) malloc(210 * sizeof(char));
    strcpy(logged, "Chatbot: ");
    strcat(logged, reply);
    chatlog(logged);
    free(logged);
}
