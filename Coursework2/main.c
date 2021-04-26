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
    int wrong_dep;
    int didnt_understand;
    // switches for questions asked by the bot
    int Q_doc_confirmation = 0;
    int Q_which_doctor = 0;
    int Q_weekday = 0;
    // checks for details
    int em_k = 0;
    int tel_k = 0;

    char* input = (char*) malloc(200*sizeof(char));
    char* processed_input = (char*) malloc(200*sizeof(char));
    char* reply = (char*) malloc(1000*sizeof(char));

    strcpy(temp_doc_name, "");
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
        wrong_dep = 0;
        didnt_understand = 0;
        
        scanf(" %[^\n]%*c", input);
        processed_input = process_input(input);
        int length = split_string(processed_input);

        if(search_for_intent_in_string(input) == 0)
            intent = 1;
        
        if(search_for_request(input) == 0)
            request = 1;
        
        if(search_for_question(input) == 0)
            question = 1;

        // =============================================================================================================
        for (int i = 0; i < length; i++)
        {
            if(strcmp(words[i], "quit") == 0 || strcmp(words[i], "bye") == 0 || strcmp(words[i], "goodbye") == 0)
            {
                quit = 1;
                strcpy(reply, "It was nice to meet you!\nHave a nice day!\n");
                break;
            }

            if(intent == 0)
                if(search_for_intent_in_word(words[i]) == 0)
                    intent = 1;
            
            // If the patient wants a list of departments or doctors
            if((strcmp(words[i], "list") == 0 || strcmp(words[i], "the") == 0 && intent == 1) || (strcmp(words[i], "list") == 0 || strcmp(words[i], "the") == 0 && question == 1) || (strcmp(words[i], "list") == 0 || strcmp(words[i], "the") == 0 && request == 1))
                list = 1;
            
            if((strcmp(words[i], "all") == 0 && intent == 1) || (strcmp(words[i], "all") == 0 && question == 1) || (strcmp(words[i], "all") == 0 && request == 1))
                all = 1;
            
            if((strcmp(words[i], "doctors") == 0 && list == 1) || (strcmp(words[i], "doctors") == 0 && question == 1) || (strcmp(words[i], "doctors") == 0 && all == 1))
                list_of_doctors = 1;
            
            if((strcmp(words[i], "departments") == 0 && list == 1) || (strcmp(words[i], "departments") == 0 && question == 1) || (strcmp(words[i], "departments") == 0 && all == 1) || (strcmp(words[i], "services") == 0 && list == 1) || (strcmp(words[i], "services") == 0 && question == 1) || (strcmp(words[i], "services") == 0 && request == 1) || (strcmp(words[i], "services") == 0 && all == 1))
                list_of_departments = 1;
            
            if(list_of_departments == 1)
            {
                strcpy(reply, list_departments());
                break;
            }

            if(list_of_doctors == 1)
            {
                if(strcmp(current_appointment.department, "") == 0 || all == 1)
                    strcpy(reply, list_all_doctors());
                else if (strcmp(current_appointment.department, "") != 0)
                    strcpy(reply, list_doctors_in_dep(current_appointment.department));
                break;
            }
            
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
                    search_for_department(words[i]);

                if(strcmp(current_appointment.doctor, "") == 0 && i > 0)
                {
                    if(search_for_doctor(words[i-1], words[i]) == 0)
                        if(strcmp(current_appointment.department, "") != 0)
                        {
                            wrong_dep = 1;
                            for(int a = 0; a < 3; a++)
                                if(strcmp(docs_in_dep[a], temp_doc_name) == 0)
                                {
                                    strcpy(current_appointment.doctor, temp_doc_name);
                                    wrong_dep = 0;
                                }
                        }
                        else
                        {
                            strcpy(current_appointment.doctor, temp_doc_name);
                            strcpy(current_appointment.department, temp_dep);
                        }
                        if(wrong_dep == 1)
                            sprintf(reply, "Dr. %s does not work for the %s department!\n", temp_doc_name, current_appointment.department);
                }
                if(strcmp(current_appointment.doctor, "") == 0)
                {
                    one_name = search_for_doctor_by_one_name(words[i]);
                    // if(one_name == 0)
                    //     break;
                }

                if(Q_doc_confirmation == 1)
                    if(strcmp(words[i], "yes") == 0)
                    {
                        if(strcmp(current_appointment.doctor, "") == 0)
                        {
                            strcpy(temp_doc_name, unconfirmed_doc_name);
                            strcpy(temp_dep, unconfirmed_dep);
                            if(strcmp(current_appointment.department, "") != 0)
                            {
                                wrong_dep = 1;
                                for(int a = 0; a < 3; a++)
                                    if(strcmp(docs_in_dep[a], temp_doc_name) == 0)
                                    {
                                        strcpy(current_appointment.doctor, temp_doc_name);
                                        wrong_dep = 0;
                                    }
                            }
                            else
                            {
                                strcpy(current_appointment.doctor, temp_doc_name);
                                strcpy(current_appointment.department, temp_dep);
                            }
                            if(wrong_dep == 1)
                                sprintf(reply, "Dr. %s does not work for the %s department!\n", temp_doc_name, current_appointment.department);
                        }
                    }
                    else if(strcmp(words[i], "no") == 0)
                    {
                        strcpy(reply, "Oh, ok.\n");
                        reset = 1;
                    }
                if(strcmp(current_appointment.date, "") == 0)
                    search_for_date_numeric(words[i]);
                if(strcmp(current_appointment.time, "") == 0)
                    search_for_time(words[i]);
            }

            if(Q_which_doctor == 1)
            {
                if(strcmp(words[i], "yes") == 0)
                {
                    strcpy(reply, "Ok, which one?\n");
                }
                else if(strcmp(words[i], "no") == 0 || strcmp(words[i], "not") == 0)
                {
                    strcpy(reply, list_doctors_in_dep(current_appointment.department));
                    didnt_understand = 0;
                    break;
                }
                else if(i > 0)
                {
                    didnt_understand = 1;
                }
                if(strcmp(current_appointment.doctor, "") != 0)
                    {
                        strcpy(reply, "");
                        didnt_understand = 0;
                    }
            }
        }
        //==========================================================================================================
        // printf("%s...", reply);
        if(didnt_understand == 1)
        {
            strcpy(reply, say_didnt_understand());
            didnt_understand = 0;
        }
        if(make_appointment == 1 || cancel_appointment == 1)
        {
            if(strcmp(current_appointment.date, "") == 0)
                search_for_date(input);
            if(strcmp(current_appointment.date, "") == 0)
                search_for_date_phrase(input);
            if(strcmp(current_appointment.time, "") == 0)
                search_for_time_phrase(input);
                
        }
        if(make_appointment == 1 && strcmp(reply, "") == 0)
            if(one_name == 0 && Q_doc_confirmation == 0 && strcmp(temp_doc_name, "") == 0 && strcmp(current_appointment.doctor, "") == 0)
                {
                    sprintf(reply, "Are you referring to dr. %s ?\n", unconfirmed_doc_name);
                    Q_doc_confirmation = 1;
                }
            else if(one_name != 0)
            {
                if(strcmp(current_appointment.department, "") == 0)
                {
                    strcpy(reply, "Ok, which department would you like to go to?\n");
                }
                if(strcmp(current_appointment.department, "") != 0 && strcmp(current_appointment.doctor, "") == 0 && 
                Q_which_doctor == 0)
                {
                    // printf("%i", Q_which_doctor);
                    strcpy(reply, "Ok, do you know which doctor you would like to see?\n");
                    Q_which_doctor = 1;
                }
                if(strcmp(current_appointment.department, "") != 0 && strcmp(current_appointment.doctor, "") != 0 && 
                strcmp(temp_date, "") == 0 && strcmp(temp_time, "") == 0)
                {
                    strcpy(reply, "Ok, when would you like to come?\n");
                }
                if(strcmp(current_appointment.department, "") != 0 && strcmp(current_appointment.doctor, "") != 0 && 
                strcmp(temp_date, "") != 0 && strcmp(temp_time, "") == 0)
                {
                    strcpy(reply, show_modified_schedule_on_date(current_appointment.doctor, temp_date));
                }
                if(strcmp(current_appointment.department, "") != 0 && strcmp(current_appointment.doctor, "") != 0 && 
                strcmp(temp_date, "") != 0 && strcmp(temp_time, "") != 0)
                {
                    if(check_availability(temp_date, temp_time, current_appointment.doctor) == 0)
                    {
                        strcpy(current_appointment.date, temp_date);
                        strcpy(current_appointment.time, temp_time);
                        struct tm wd = string_to_tm(current_appointment.date);
                        strcpy(current_appointment.weekday, Weekday[wd.tm_wday]);
                    }
                    else
                        strcpy(reply, "That is not a valid hour! Try again!\n");
                }
                if(strcmp(current_appointment.department, "") != 0 && strcmp(current_appointment.doctor, "") != 0 && 
                strcmp(current_appointment.date, "") != 0 && strcmp(current_appointment.time, "") != 0)
                {
                    respond("Alright, I will need you to provide some details so that I can finalise the appointment.\nWhat is your name?\n");
                    scanf(" %[^\n]%*c", input);
                    process_input(input);
                    strcpy(current_appointment.name, input);
                    respond("Ok, what is your email address?\n");
                    while (1)
                    {
                        scanf("%s", input);
                        for (int a = 0; a < strlen(input); a++)
                        {
                            if (input[a] == '@')
                            em_k = 1;
                        }
                        if (em_k == 0)
                            respond("Invalid email! Please try again:\n");
                        else
                            break;
                    }
                    process_input(input);
                    strcpy(current_appointment.email, input);
                    respond("Your telephone number please.\n");
                    while (1)
                    {
                        scanf("%s", input);
                        for (int a = 0; a < strlen(input); a++)
                        {
                            if (isdigit(input[a]) == 0)
                            tel_k = 1;
                        }
                        if (tel_k == 1)
                            respond("Invalid telephone number! Please only enter digits:\n");
                        else
                            break;
                    }
                    process_input(input);
                    strcpy(current_appointment.tel, input);
                    respond("How old are you?\n");
                    while (1)
                    {
                        scanf("%s", input);
                        for (int a = 0; a < strlen(input); a++)
                        {
                            if (isdigit(input[a]) == 0)
                            tel_k = 1;
                        }
                        if (tel_k == 1)
                            respond("Invalid age! Please only enter digits:\n");
                        else
                            break;
                    }
                    process_input(input);
                    strcpy(current_appointment.age, input);
                }
                if(strcmp(current_appointment.department, "") != 0 && strcmp(current_appointment.doctor, "") != 0 && 
                strcmp(current_appointment.date, "") != 0 && strcmp(current_appointment.time, "") != 0 && 
                strcmp(current_appointment.name, "") != 0 && strcmp(current_appointment.email, "") != 0 && 
                strcmp(current_appointment.tel, "") != 0 && strcmp(current_appointment.age, "") != 0 && 
                strcmp(current_appointment.weekday, "") != 0)
                {
                    sprintf(reply, "Here is a recap of the details you gave me:\nName: %s\nEmail: %s\nTel: %s\nAge: %s\nDepartment: %s\nDoctor: %s\nDate: %s\nWeekday: %s\nTime: %s\n",
                    current_appointment.name, current_appointment.email, current_appointment.tel, current_appointment.age,
                    current_appointment.department, current_appointment.doctor, current_appointment.date,
                    current_appointment.weekday, current_appointment.time);
                }
            }

        if(strcmp(current_appointment.department, "") != 0)
            printf("%s\n", current_appointment.department);
        if(strcmp(current_appointment.doctor, "") != 0)
            printf("%s\n", current_appointment.doctor);
        if(strcmp(current_appointment.date, "") != 0)
            printf("%s\n", current_appointment.date);
        if(strcmp(current_appointment.time, "") != 0)
            printf("%s\n", current_appointment.time);

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