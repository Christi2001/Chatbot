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
    int make;
    int cancel_appointment = 0;
    int cancel;
    int reset;
    int quit;
    int intent;
    int request;
    int question;
    int all;
    int list;
    int list_of_doctors;
    int list_of_departments;
    int one_name;
    // switches for questions asked by the bot
    int Q_doc_confirmation = 0;
    int Q_which_doctor = 0;

    char* input = (char*) malloc(200*sizeof(char));
    char* processed_input = (char*) malloc(200*sizeof(char));
    char* reply = (char*) malloc(1000*sizeof(char));

    temp_doc_name = (char*) malloc(30*sizeof(char));
    temp_dep = (char*) malloc(20*sizeof(char));
    temp_date = (char*) malloc(11*sizeof(char));
    temp_sec = 0;
    
    load_appointments();
    load_doctors();
    strcpy(reply, say_introduction());
    respond(reply);
    strcpy(reply, "");
    
    while(1)
    {
        make = 0;
        cancel = 0;
        reset = 0;
        quit = 0;
        intent = 0;
        request = 0;
        question = 0;
        all = 0;
        list = 0;
        list_of_doctors = 0;
        list_of_departments = 0;
        one_name = 1;
        
        scanf(" %[^\n]%*c", input);
        processed_input = process_input(input);
        int length = split_string(processed_input);

        if(search_for_intent_in_string(input) == 0)
            intent = 1;
        
        if(search_for_request(input) == 0)
        {
            // printf("request...\n");
            request = 1;
        }
        if(search_for_question(input) == 0)
        {
            // printf("question...\n");
            question = 1;
        }
        for (int i = 0; i < length; i++)
        {
            if(strcmp(words[i], "quit") == 0 || strcmp(words[i], "bye") == 0 || strcmp(words[i], "goodbye") == 0)
            {
                quit = 1;
                strcpy(reply, "It was nice to meet you!\nHave a nice day!\n");
                break;
            }
            // printf("%d", make_appointment);
            // printf("%s\n", words[i]);

            // If the patient wants a list of departments or doctors
            if((strcmp(words[i], "list") == 0 || strcmp(words[i], "the") == 0 && intent == 1) || (strcmp(words[i], "list") == 0 || strcmp(words[i], "the") == 0 && question == 1) || (strcmp(words[i], "list") == 0 || strcmp(words[i], "the") == 0 && request == 1))
            {
                // printf("list...\n");
                list = 1;
            }
            if((strcmp(words[i], "all") == 0 && intent == 1) || (strcmp(words[i], "all") == 0 && question == 1) || (strcmp(words[i], "all") == 0 && request == 1))
            {
                // printf("list...\n");
                all = 1;
            }
            if((strcmp(words[i], "doctors") == 0 && list == 1) || (strcmp(words[i], "doctors") == 0 && question == 1) || (strcmp(words[i], "doctors") == 0 && all == 1))
            {
                // printf("list of doc...\n");
                list_of_doctors = 1;
            }
            if((strcmp(words[i], "departments") == 0 && list == 1) || (strcmp(words[i], "departments") == 0 && question == 1) || (strcmp(words[i], "departments") == 0 && all == 1) || (strcmp(words[i], "services") == 0 && list == 1) || (strcmp(words[i], "services") == 0 && question == 1) || (strcmp(words[i], "services") == 0 && request == 1) || (strcmp(words[i], "services") == 0 && all == 1))
            {
                // printf("list of dep...\n");
                list_of_departments = 1;
            }
            if(list_of_departments == 1)
            {
                strcpy(reply, list_departments());
                break;
            }
            if(list_of_doctors == 1)
            {
                // printf("listing doctors...\n");
                if(strcmp(current_appointment.department, "") == 0 || all == 1)
                    strcpy(reply, list_all_doctors());
                else if (strcmp(current_appointment.department, "") != 0)
                    strcpy(reply, list_doctors_in_dep(current_appointment.department));
                break;
            }
            
            if(intent == 0)
                if(search_for_intent_in_word(words[i]) == 0)
                    intent = 1;
            
            // If the patient wants to make or cancel an appointment
            if((strcmp(words[i], "make") == 0 || strcmp(words[i], "get") == 0 && intent == 1) || (strcmp(words[i], "make") == 0 || strcmp(words[i], "get") == 0 && question == 1))
                make = 1;
            if(strcmp(words[i], "appointment") == 0 && make == 1)
                make_appointment = 1;
            
            if((strcmp(words[i], "cancel") == 0 && intent == 1) || (strcmp(words[i], "cancel") == 0 && question == 1))
                cancel = 1;
            if(strcmp(words[i], "appointment") == 0 && cancel == 1)
                cancel_appointment = 1;
            
            if(make_appointment == 1)
            {
                if(strcmp(current_appointment.department, "") == 0)
                {
                    // printf("1\n");
                    search_for_department(words[i]);
                    // printf("2\n");
                }
                if(strcmp(current_appointment.doctor, "") == 0 && i > 0)
                {
                    search_for_doctor(words[i-1], words[i]);
                }
                if(strcmp(current_appointment.doctor, "") == 0)
                    one_name = search_for_doctor_by_one_name(words[i]);
                
                if(Q_doc_confirmation == 1)
                    if(strcmp(words[i], "yes") == 0)
                    {
                        if(strcmp(current_appointment.doctor, "") == 0)
                        {
                            strcpy(current_appointment.doctor, temp_doc_name);
                            strcpy(current_appointment.department, temp_dep);
                            // time = 1;
                        }
                    }
                    else if(strcmp(words[i], "no") == 0)
                    {
                        strcpy(reply, "Oh, ok.\n");
                        reset = 1;
                    }
            }

            if(Q_which_doctor == 1)
            {
                if(strcmp(words[i], "yes") == 0)
                {
                    strcpy(reply, "Ok, which one?\n");
                    if(strcmp(current_appointment.doctor, "") != 0)
                        strcpy(reply, "Ok\n");
                }
                else if(strcmp(words[i], "no") == 0 || strcmp(words[i], "not") == 0)
                {
                    strcpy(reply, list_doctors_in_dep(current_appointment.department));
                }
            }
        }
        // printf("%s...", reply);
        if(make_appointment == 1 && strcmp(reply, "") == 0)
            if(one_name == 0 && Q_doc_confirmation == 0 && strcmp(current_appointment.doctor, "") == 0)
                    {
                        sprintf(reply, "Are you referring to dr. %s ?\n", temp_doc_name);
                        Q_doc_confirmation = 1;
                    }
            else if(one_name != 0)
            {
                if(strcmp(current_appointment.department, "") == 0)
                {
                    strcpy(reply, "Ok, which department would you like to go to?\n");
                }
                else if(strcmp(current_appointment.doctor, "") == 0 && Q_which_doctor == 0)
                {
                    // printf("%i", Q_which_doctor);
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

        if(quit == 1)
            exit(0);
        strcpy(reply, "");
    }

    return 0;
}