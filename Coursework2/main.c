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
    current_appointment.name = (char*) malloc(40*sizeof(char));
    current_appointment.email = (char*) malloc(40*sizeof(char));
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

    int length_unprocessed;
    int length_processed;
    // switches for context
    int make_appointment = 0;
    int make;
    int cancel_appointment = 0;
    int cancel;
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
    int incorrect_info = 0;
    // switches for questions asked by the bot
    int Q_doc_confirmation = 0;
    int Q_which_doctor = 0;
    int Q_correct_info = 0;
    int Q_anything_else = 0;
    int Q_cancel_details = 0;
    // checks for details
    int em_k = 0;
    int tel_k = 0;
    int age_k = 0;
    int age;

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
        quit = 0;
        intent = 0;
        request = 0;
        question = 0;
        all = 0;
        list = 0;
        list_of_doctors = 0;
        list_of_departments = 0;
        one_name = 0;
        wrong_dep = 0;
        
        scanf(" %[^\n]%*c", input);
        processed_input = process_input(input);
        length_processed = split_string(processed_input);

        if(search_for_intent_in_string(input) == 0)
            intent = 1;
        
        if(search_for_request(input) == 0)
            request = 1;
        
        if(search_for_question(input) == 0)
            question = 1;

        // =============================================================================================================
        for (int i = 0; i < length_processed; i++)
        {
            // printf("word[%i]: %s\n", i, words[i]);
            if(strcmp(words[i], "quit") == 0 || strcmp(words[i], "exit") == 0 || strcmp(words[i], "bye") == 0 || strcmp(words[i], "goodbye") == 0)
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
            if((strcmp(words[i], "make") == 0 || strcmp(words[i], "get") == 0 && intent == 1) || ((strcmp(words[i], "make") == 0 || strcmp(words[i], "get") == 0) && question == 1))
                make = 1;
            if(strcmp(words[i], "appointment") == 0 && make == 1)
            {
                make_appointment = 1;
                cancel_appointment = 0;
                strcpy(reply, "OK. \n");
            }

            if((strcmp(words[i], "cancel") == 0 && intent == 1) || (strcmp(words[i], "cancel") == 0 && question == 1))
                cancel = 1;
            if(strcmp(words[i], "appointment") == 0 && cancel == 1)
            {
                cancel_appointment = 1;
                make_appointment = 0;
            }

            if(make_appointment == 1 || cancel_appointment == 1)
            {
                if(strcmp(current_appointment.department, "") == 0)
                    search_for_department(words[i]);

                if(strcmp(current_appointment.doctor, "") == 0)
                {
                    if(i > 0)
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
                    if(search_for_doctor_by_one_name(words[i]) == 0)
                        one_name = 1;
                }

                if(Q_doc_confirmation == 1)
                {
                    if(strcmp(words[i], "yes") == 0)
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
                                        strcpy(reply, "OK. \n");
                                        Q_doc_confirmation = 0;
                                    }
                            }
                            else
                            {
                                strcpy(current_appointment.doctor, temp_doc_name);
                                strcpy(current_appointment.department, temp_dep);
                                Q_doc_confirmation = 0;
                            }
                            if(wrong_dep == 1)
                                sprintf(reply, "Dr. %s does not work for the %s department!\n", temp_doc_name, current_appointment.department);
                        }
                    else if(strcmp(words[i], "no") == 0)
                        strcpy(reply, "Oh, OK. \n");
                }
            }

            if(Q_which_doctor == 1)
            {
                if(strcmp(words[i], "yes") == 0)
                {
                    strcpy(reply, "OK, which one?\n");
                    if(strcmp(current_appointment.doctor, "") != 0)
                    {
                        strcpy(reply, "OK. \n");
                        Q_which_doctor == 0;
                    }
                }
                else if(strcmp(words[i], "no") == 0 || strcmp(words[i], "not") == 0)
                {
                    strcpy(reply, list_doctors_in_dep(current_appointment.department));
                    Q_which_doctor == 0;
                }
            }

            if(Q_correct_info == 1)
            {
                if(strcmp(words[i], "yes") == 0)
                {
                    save_appointment(current_appointment);
                    load_appointments();
                    make_appointment = 0;
                    strcpy(current_appointment.name, "");
                    strcpy(current_appointment.email, "");
                    strcpy(current_appointment.tel, "");
                    strcpy(current_appointment.age, "");
                    strcpy(current_appointment.department, "");
                    strcpy(current_appointment.doctor, "");
                    strcpy(current_appointment.date, "");
                    strcpy(current_appointment.weekday, "");
                    strcpy(current_appointment.time, "");
                    strcpy(reply, ask_for_other_questions());
                    Q_anything_else = 1;
                    Q_correct_info = 0;
                }
                else if(strcmp(words[i], "no") == 0 || strcmp(words[i], "not") == 0)
                {
                    incorrect_info = 1;
                    strcpy(reply, "OK. What should I change?\n");
                    Q_correct_info = 0;
                }
            }

            if(incorrect_info == 1)
            {
                if(strcmp(words[i], "name") == 0)
                    strcpy(current_appointment.name, "");
                if(strcmp(words[i], "email") == 0)
                    strcpy(current_appointment.email, "");
                if(strcmp(words[i], "telephone") == 0)
                    strcpy(current_appointment.tel, "");
                if(strcmp(words[i], "age") == 0)
                    strcpy(current_appointment.age, "");
                if(strcmp(words[i], "doctor") == 0)
                {
                    strcpy(current_appointment.doctor, "");
                    strcpy(current_appointment.date, "");
                    strcpy(current_appointment.weekday, "");
                    strcpy(current_appointment.time, "");
                }
                if(strcmp(words[i], "department") == 0)
                {
                    strcpy(current_appointment.department, "");
                    strcpy(current_appointment.doctor, "");
                    strcpy(current_appointment.date, "");
                    strcpy(current_appointment.weekday, "");
                    strcpy(current_appointment.time, "");
                }
                if(strcmp(words[i], "date") == 0)
                {
                    strcpy(current_appointment.date, "");
                    strcpy(current_appointment.weekday, "");
                    strcpy(current_appointment.time, "");
                }
                if(strcmp(words[i], "time") == 0)
                {
                    strcpy(temp_date, current_appointment.date);
                    strcpy(current_appointment.date, "");
                    strcpy(current_appointment.weekday, "");
                    strcpy(current_appointment.time, "");
                }
                if(strcmp(current_appointment.department, "") == 0 || strcmp(current_appointment.doctor, "") == 0 || 
                strcmp(current_appointment.date, "") == 0 || strcmp(current_appointment.time, "") == 0 || 
                strcmp(current_appointment.name, "") == 0 || strcmp(current_appointment.email, "") == 0 || 
                strcmp(current_appointment.tel, "") == 0 || strcmp(current_appointment.age, "") == 0 || 
                strcmp(current_appointment.weekday, "") == 0)
                    strcpy(reply, "");
            }

            if(Q_anything_else == 1)
                if(strcmp(words[i], "no") == 0)
                {
                    quit = 1;
                    strcpy(reply, "Alright then, it was nice to meet you!\nHave a nice day!\n");
                    break;
                }
        }
        //==========================================================================================================

        if(one_name == 1 && Q_doc_confirmation == 0 && strcmp(temp_doc_name, "") == 0)
        {
            sprintf(reply, "Are you referring to dr. %s?\n", unconfirmed_doc_name);
            Q_doc_confirmation = 1;
        }

        //search for date and time
        if(make_appointment == 1 || cancel_appointment == 1)
        {
            if(strcmp(current_appointment.date, "") == 0)
            {
                search_for_date(input);
                search_for_date_phrase(input);
            }
            if(strcmp(current_appointment.time, "") == 0)
                search_for_time_phrase(input);
            length_unprocessed = split_string(input);
            for(int i = 0; i < length_unprocessed; i++)
            {
                if(strcmp(current_appointment.date, "") == 0)
                    search_for_date_numeric(words[i]);
                if(strcmp(current_appointment.time, "") == 0)
                    search_for_time(words[i]);
            }
        }
    
        // ask for all details of an appointment
        if(make_appointment == 1 && (strcmp(reply, "") == 0 || strcmp(reply, "OK. \n") == 0))
        {
            if(strcmp(reply, "OK. \n") == 0)
                reply[4] = '\0';

            if(strcmp(current_appointment.department, "") == 0)
            {
                strcat(reply, "Which department would you like to go to?\n");
            }

            if(strcmp(current_appointment.department, "") != 0 && strcmp(current_appointment.doctor, "") == 0 && 
            Q_which_doctor == 0)
            {
                // printf("%i", Q_which_doctor);
                strcat(reply, "Do you know which doctor you would like to see?\n");
                Q_which_doctor = 1;
            }

            if(strcmp(current_appointment.department, "") != 0 && strcmp(current_appointment.doctor, "") != 0 && 
            strcmp(temp_date, "") == 0 && strcmp(temp_time, "") == 0)
                strcat(reply, "When would you like to come?\n");

            if(strcmp(current_appointment.department, "") != 0 && strcmp(current_appointment.doctor, "") != 0 && 
            strcmp(temp_date, "") != 0 && strcmp(temp_time, "") == 0)
                strcat(reply, show_modified_schedule_on_date(current_appointment.doctor, temp_date));

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
                    strcat(reply, "That is not a valid hour! Try again!\n");
            }

            if(strcmp(current_appointment.department, "") != 0 && strcmp(current_appointment.doctor, "") != 0 && 
            strcmp(current_appointment.date, "") != 0 && strcmp(current_appointment.time, "") != 0)
            {
                if(incorrect_info != 1)
                    respond("Alright, I will need you to provide some details so that I can finalise the appointment.\n");
                if(strcmp(current_appointment.name, "") == 0)
                {
                    respond("What is your name?\n");
                    scanf(" %[^\n]%*c", input);
                    if(input[strlen(input) - 1] == '.')
                        input[strlen(input) - 1] = '\0';
                    strcpy(current_appointment.name, input);
                    process_input(input);
                }
                if(strcmp(current_appointment.email, "") == 0)
                {
                    respond("OK, what is your email address?\n");
                    while (1)
                    {
                        em_k = 0;
                        scanf("%s", input);
                        char* logged = (char*) malloc(210 * sizeof(char));
                        strcpy(logged, "Patient: ");
                        strcat(logged, input);
                        chatlog(logged);
                        free(logged);
                        if(input[strlen(input) - 1] == '.')
                            input[strlen(input) - 1] = '\0';
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
                    strcpy(current_appointment.email, input);
                }
                if(strcmp(current_appointment.tel, "") == 0)
                {
                    respond("Your telephone number please.\n");
                    while (1)
                    {
                        tel_k = 0;
                        scanf("%s", input);
                        char* logged = (char*) malloc(210 * sizeof(char));
                        strcpy(logged, "Patient: ");
                        strcat(logged, input);
                        chatlog(logged);
                        free(logged);
                        if(input[strlen(input) - 1] == '.')
                            input[strlen(input) - 1] = '\0';
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
                    strcpy(current_appointment.tel, input);
                }
                if(strcmp(current_appointment.age, "") == 0)
                {
                    respond("How old are you?\n");
                    while (1)
                    {
                        age_k = 0;
                        scanf("%s", input);
                        char* logged = (char*) malloc(210 * sizeof(char));
                        strcpy(logged, "Patient: ");
                        strcat(logged, input);
                        chatlog(logged);
                        free(logged);
                        if(input[strlen(input) - 1] == '.')
                            input[strlen(input) - 1] = '\0';
                        for (int a = 0; a < strlen(input); a++)
                        {
                            if (isdigit(input[a]) == 0)
                            age_k = 1;
                        }
                        age = atoi(input);
                        if(age > 150 || age < 0)
                            age_k = 2;
                        if (age_k == 1)
                            respond("Invalid age! Please only enter digits:\n");
                        else if(age_k == 2)
                            respond("Invalid age!\n");
                        else
                            break;
                    }
                    strcpy(current_appointment.age, input);
                }
            }
            if(strcmp(current_appointment.department, "") != 0 && strcmp(current_appointment.doctor, "") != 0 && 
            strcmp(current_appointment.date, "") != 0 && strcmp(current_appointment.time, "") != 0 && 
            strcmp(current_appointment.name, "") != 0 && strcmp(current_appointment.email, "") != 0 && 
            strcmp(current_appointment.tel, "") != 0 && strcmp(current_appointment.age, "") != 0 && 
            strcmp(current_appointment.weekday, "") != 0)
            {
                sprintf(reply, "Here is a recap of the details you gave me:\nName: %s\nEmail: %s\nTel: %s\nAge: %s\nDepartment: %s\nDoctor: %s\nDate: %s\nWeekday: %s\nTime: %s\nIs the information correct? (If not, tell me what to change!)\n",
                current_appointment.name, current_appointment.email, current_appointment.tel, current_appointment.age,
                current_appointment.department, current_appointment.doctor, current_appointment.date,
                current_appointment.weekday, current_appointment.time);
                Q_correct_info = 1;
            }
        }

        if(cancel_appointment == 1)
        {
            if(Q_cancel_details == 0)
            {
                respond("Ok, I will need you to provide some details so that I can find your appointment.\n");
                Q_cancel_details = 1;
            }
            if(strcmp(current_appointment.name, "") == 0)
            {
                respond("What is your name?\n");
                scanf(" %[^\n]%*c", input);
                if(input[strlen(input) - 1] == '.')
                    input[strlen(input) - 1] = '\0';
                strcpy(current_appointment.name, input);
                process_input(input);
            }
            if(strcmp(current_appointment.name, "") != 0 && strcmp(current_appointment.tel, "") == 0)
            {
                respond("What phone number did you use?\n");
                while (1)
                {
                    tel_k = 0;
                    scanf("%s", input);
                    char* logged = (char*) malloc(210 * sizeof(char));
                    strcpy(logged, "Patient: ");
                    strcat(logged, input);
                    chatlog(logged);
                    free(logged);
                    if(input[strlen(input) - 1] == '.')
                        input[strlen(input) - 1] = '\0';
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
                strcpy(current_appointment.tel, input);
            }
            if(strcmp(current_appointment.name, "") != 0 && strcmp(current_appointment.tel, "") != 0 && 
            strcmp(temp_doc_name, "") == 0)
                strcpy(reply, "Which doctor did you make the appointment for?\n");

            if(strcmp(current_appointment.name, "") != 0 && strcmp(current_appointment.tel, "") != 0 && 
            strcmp(current_appointment.doctor, "") != 0 && strcmp(temp_date, "") == 0)
                strcpy(reply, "What date is it on?\n");

            if(strcmp(current_appointment.name, "") != 0 && strcmp(current_appointment.tel, "") != 0 && 
            strcmp(current_appointment.doctor, "") != 0 && strcmp(temp_date, "") != 0 && strcmp(temp_time, "") == 0)
                strcpy(reply, "And for what time?\n");

            if(strcmp(temp_date, "") != 0 && strcmp(temp_time, "") != 0)
                if(check_availability(temp_date, temp_time, current_appointment.doctor) == 1)
                {
                    strcpy(current_appointment.date, temp_date);
                    strcpy(current_appointment.time, temp_time);
                }
                else
                {
                    strcpy(current_appointment.name, "");
                    strcpy(current_appointment.tel, "");
                    strcpy(current_appointment.doctor, "");
                    strcpy(current_appointment.department, "");
                    strcpy(current_appointment.date, "");
                    strcpy(current_appointment.time, "");
                    strcpy(temp_doc_name, "");
                    strcpy(temp_dep, "");
                    strcpy(temp_date, "");
                    strcpy(temp_time, "");
                    cancel_appointment = 0;
                    Q_cancel_details = 0;
                    respond("There is no appointment made with the details you provided!\n");
                    strcpy(reply, ask_for_other_questions());
                    Q_anything_else = 1;
                }
            if(strcmp(current_appointment.name, "") != 0 && strcmp(current_appointment.tel, "") != 0 &&
            strcmp(current_appointment.doctor, "") != 0 && strcmp(current_appointment.date, "") != 0 &&
            strcmp(current_appointment.time, "") != 0)
            {
                if(delete_appointment(current_appointment) == 0)
                {
                    strcpy(current_appointment.name, "");
                    strcpy(current_appointment.tel, "");
                    strcpy(current_appointment.doctor, "");
                    strcpy(current_appointment.department, "");
                    strcpy(current_appointment.date, "");
                    strcpy(current_appointment.time, "");
                    strcpy(temp_doc_name, "");
                    strcpy(temp_dep, "");
                    strcpy(temp_date, "");
                    strcpy(temp_time, "");
                    respond("Done!\n");
                    load_appointments();
                    Q_cancel_details = 0;
                    cancel_appointment = 0;
                    strcpy(reply, ask_for_other_questions());
                    Q_anything_else = 1;
                }
                else
                {
                    strcpy(current_appointment.name, "");
                    strcpy(current_appointment.tel, "");
                    strcpy(current_appointment.doctor, "");
                    strcpy(current_appointment.department, "");
                    strcpy(current_appointment.date, "");
                    strcpy(current_appointment.time, "");
                    strcpy(temp_doc_name, "");
                    strcpy(temp_dep, "");
                    strcpy(temp_date, "");
                    strcpy(temp_time, "");
                    cancel_appointment = 0;
                    Q_cancel_details = 0;
                    respond("There is no appointment made with the details you provided!\n");
                    strcpy(reply, ask_for_other_questions());
                    Q_anything_else = 1;
                }
            }
        }

        for(int i = 0; i < length_processed; i++)
        {
            for(int j = 0; j < 20; j++)
                words[i][j] = '\0';
        }
        if(strcmp(reply, "") == 0)
            strcpy(reply, say_didnt_understand());
        respond(reply);

        if(quit == 1)
            exit(0);
        strcpy(reply, "");
    }

    return 0;
}