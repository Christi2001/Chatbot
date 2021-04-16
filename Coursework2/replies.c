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