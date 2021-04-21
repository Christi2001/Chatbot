#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "replies.h"
#include "processing.h"

char* say_introduction()
{
    char* string = "Hello! My name is Bob and I am your virtual assistant.\nHow may I help you?\n";
    return string;
}

void say_hello_name(char* name)
{
    // printf("");
}

void say_goodbye()
{

}

void ask_appointment_details(Appointment appointment)
{

}

void ask_for_other_questions()
{
    
}

void didnt_understand()
{

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
    for(int i = 0; i < 10; i++)
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