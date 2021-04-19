#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "processing.h"
#include "appointments.h"
#include "replies.h"

int main()
{
    // Appointment current_appointment;
    current_appointment.app_ID = (char*) malloc(5*sizeof(char));
    current_appointment.name = (char*) malloc(30*sizeof(char));
    current_appointment.email = (char*) malloc(30*sizeof(char));
    current_appointment.tel = (char*) malloc(12*sizeof(char));
    current_appointment.age = (char*) malloc(4*sizeof(char));
    current_appointment.department = (char*) malloc(20*sizeof(char));
    current_appointment.doctor = (char*) malloc(20*sizeof(char));
    current_appointment.date = (char*) malloc(11*sizeof(char));
    current_appointment.weekday = (char*) malloc(4*sizeof(char));
    current_appointment.time = (char*) malloc(6*sizeof(char));
    
    strcpy(current_appointment.name, "");
    strcpy(current_appointment.email, "");
    strcpy(current_appointment.tel, "");
    strcpy(current_appointment.age, "");
    strcpy(current_appointment.department, "");
    strcpy(current_appointment.doctor, "");
    strcpy(current_appointment.date, "");
    strcpy(current_appointment.weekday, "");
    strcpy(current_appointment.time, "");

    // switches for context
    int make_appointment = 0;
    int make = 0;
    int cancel_appointment = 0;
    int cancel = 0;
    int intent;
    int one_name = 1;
    // switches for questions asked by the bot
    int Q_doc_confirmation = 0;
    int Q_which_doctor = 0;
    // int not;

    char* input = (char*) malloc(200*sizeof(char));
    char* processed_input = (char*) malloc(200*sizeof(char));
    char* reply = (char*) malloc(200*sizeof(char));

    doc_full_name = (char*) malloc(30*sizeof(char));
    
    load_appointments();
    load_doctors();
    strcpy(reply, say_introduction());
    respond(reply);
    
    while(1)
    {
        intent = 0;
        // not = 0;
        
        scanf(" %[^\n]%*c", input);
        processed_input = process_input(input);
        int length = split_string(processed_input);
        if(search_for_intent_in_string(processed_input) == 0)
            intent = 1;
        for (int i = 0; i < length; i++)
        {
            printf("%d", make_appointment);
            // printf("%s\n", words[i]);
            if(intent == 0)
                if(search_for_intent_in_word(words[i]) == 0)
                    intent = 1;
            
            if(strcmp(words[i], "make") == 0 && intent == 1)
                make = 1;
            if(strcmp(words[i], "appointment") == 0 && make == 1)
                make_appointment = 1;

            
            if(strcmp(words[i], "cancel") == 0 && intent == 1)
                cancel = 1;
            if(strcmp(words[i], "appointment") == 0 && cancel == 1)
                cancel_appointment = 1;
            
            if(make_appointment == 1)
            {
                if(strcmp(current_appointment.department, "") == 0)
                {
                    printf("1");
                    search_for_department(words[i]);
                    printf("2");
                }
                if(strcmp(current_appointment.doctor, "") == 0 && i > 0)
                {
                    search_for_doctor(words[i-1], words[i]);
                }
                if(strcmp(current_appointment.doctor, "") == 0)
                    one_name = search_for_doctor_by_one_name(words[i]);
                if(one_name == 0 && Q_doc_confirmation == 0)
                {
                    sprintf(reply, "Are you referring to dr. %s ?\n", doc_full_name);
                    Q_doc_confirmation = 1;
                }
                if(Q_doc_confirmation == 1)
                    if(strcmp(words[i], "yes") == 0)
                    {
                        if(strcmp(current_appointment.doctor, "") == 0)
                        {
                            strcpy(current_appointment.doctor, doc_full_name);
                            // printf("123\n");
                        }
                    }
            }

            if(Q_which_doctor == 1)
            {
                if(strcmp(words[i], "yes") == 0)
                {
                    if(strcmp(current_appointment.doctor, "") == 0)
                        strcpy(reply, "Ok, which one?\n");
                }
                else if(strcmp(words[i], "no") == 0)
                {
                    strcpy(reply, list_doctors_in_dep(current_appointment.department));
                }
            }
        }
        if(make_appointment == 1 && one_name != 0)
        {
            if(strcmp(current_appointment.department, "") == 0)
            {
                strcpy(reply, "Ok, which department would you like to go to?\n");
            }
            else if(strcmp(current_appointment.doctor, "") == 0 && Q_which_doctor == 0)
            {
                printf("%i", Q_which_doctor);
                strcpy(reply, "Ok, do you know which doctor you would like to see?\n");
                Q_which_doctor = 1;
            }
        }

        if(strcmp(current_appointment.department, "") != 0)
            printf("%s\n", current_appointment.department);
        if(strcmp(current_appointment.doctor, "") != 0)
            printf("%s\n", current_appointment.doctor);

        for(int i = 0; i < length; i++)
        {
            for(int j = 0; j < 20; j++)
                words[i][j] = '\0';
        }
        respond(reply);
    }

    return 0;
}