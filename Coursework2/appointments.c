#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "appointments.h"


char Weekday[7][4] = {"Sun\0", "Mon\0", "Tue\0", "Wed\0", "Thu\0", "Fri\0", "Sat\0"};
char hours[24][6] = {"08:00\0", "08:30\0", "09:00\0", "09:30\0", "10:00\0", "10:30\0",
                    "11:00\0", "11:30\0", "12:00\0", "12:30\0", "13:00\0", "13:30\0",
                    "14:00\0", "14:30\0", "15:00\0", "15:30\0", "16:00\0", "16:30\0",
                    "17:00\0", "17:30\0", "18:00\0", "18:30\0", "19:00\0", "19:30\0"};


struct tm current_day()
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    // printf("now: %s %02d-%02d-%d %02d:%02d:%02d\n", Weekday[tm.tm_wday], tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
    return tm;
}

time_t string_to_sec(char* str)
{
    struct tm t1;
    memset(&t1, 0, sizeof(t1));
    strptime(str, "%d.%m.%Y", &t1);
    time_t t = mktime(&t1);
    return t;
}

struct tm string_to_tm(char* date)
{
    struct tm t;
    memset(&t, 0, sizeof(t));
    strptime(date, "%d.%m.%Y", &t);
    return t;
}

int check_availability(char* date, char* time, char* doc_name)
{
    struct tm t1 = string_to_tm(date);
    char wd[4];
    strcpy(wd, Weekday[t1.tm_wday]);
    for(int a = 0; a < TOTAL_NUM_DEP; a++)
        for(int b = 0; b < NUM_DOCS_IN_ONE_DEP; b++)
            if(strcmp(doc_name, department[a].doctors[b].full_name) == 0)
            {
            for(int i = 0; i < Current_num_appointments; i++)
                if(strcmp(department[a].doctors[b].full_name, appointment[i].doctor) == 0 && strcmp(date, appointment[i].date) == 0 && strcmp(time, appointment[i].time) == 0)
                    return 1;

            for(int i = 0; i < NUM_WORKDAYS_PER_WEEK; i++)
                if(strcmp(wd, department[a].doctors[b].schedule[i].weekday) == 0)
                    for (int j = 0; j < 24; j++)
                    {
                        if(strcmp(time, hours[j]) == 0)
                            if(department[a].doctors[b].schedule[i].session[j] == '1')
                                return 0;
                    }
            }
    return -1;
}

int doctor_schedule(char* doc_name, char* weekday)
{
    for(int i = 0; i < TOTAL_NUM_DEP; i++)
        for(int j = 0; j < NUM_DOCS_IN_ONE_DEP; j++)
            if(strcmp(department[i].doctors[j].full_name, doc_name) == 0)
                for(int k = 0; k < NUM_WORKDAYS_PER_WEEK; k++)
                    if(strcmp(department[i].doctors[j].schedule[k].weekday, weekday) == 0)
                    {
                        strcpy(normal_schedule.weekday, department[i].doctors[j].schedule[k].weekday);
                        strcpy(normal_schedule.session, department[i].doctors[j].schedule[k].session);
                        return 0;
                    }
    return 1;
}

int doctor_schedule_on_date(char* doc_name, char* date)
{
    struct tm t1 = string_to_tm(date);
    char wd[4];
    strcpy(wd, Weekday[t1.tm_wday]);
    if(doctor_schedule(doc_name, wd) == 0)
    {
        strcpy(modified_schedule.weekday, normal_schedule.weekday);
        strcpy(modified_schedule.session, normal_schedule.session);
        for(int i = 0; i < 24; i++)
            if(modified_schedule.session[i] == '1')
                if(check_availability(date, hours[i], doc_name) == 1)
                    modified_schedule.session[i] = '2';
        return 0;
    }
    return 1;
}

int save_appointment(Appointment app)
{
    FILE* file;
    file = fopen("appointments.txt", "a");
    if(!file)
    {
        printf("Cannot open file \"appointments.txt\"!");
        return 1;
    }
    Current_num_appointments++;
    sprintf(app.app_ID, "%d", 1000 + Current_num_appointments);
    fprintf(file, "%s\n", app.app_ID);
    fprintf(file, "%s\n", app.name);
    fprintf(file, "%s\n", app.email);
    fprintf(file, "%s\n", app.tel);
    fprintf(file, "%s\n", app.age);
    fprintf(file, "%s\n", app.department);
    fprintf(file, "%s\n", app.doctor);
    fprintf(file, "%s\n", app.date);
    fprintf(file, "%s\n", app.weekday);
    fprintf(file, "%s\n\n", app.time);

    fclose(file);
    return 0;
}

int cancel_appointment(Appointment app)
{
    int index = -1;
    for(int i = 0; i < Current_num_appointments; i++)
    {
        printf("bruh\n");
        printf("%s\n", appointment[i].name);
        printf("%s\n", appointment[i].tel);
        printf("%s\n", appointment[i].doctor);
        printf("%s\n", appointment[i].date);
        printf("%s\n\n", appointment[i].time);
        if(strcmp(appointment[i].name, app.name) == 0 && strcmp(appointment[i].tel, app.tel) == 0 && strcmp(appointment[i].doctor, app.doctor) == 0 && strcmp(appointment[i].date, app.date) == 0 && strcmp(appointment[i].time, app.time) == 0)
            {
                index = i;
                break;
            }
    }

    if(index != -1)
    {
        for(int i = index; i < Current_num_appointments - 1; i++)
        {
            sprintf(appointment[i].app_ID, "%d", 1001 + i);
            strcpy(appointment[i].name, appointment[i+1].name);
            strcpy(appointment[i].email, appointment[i+1].email);
            strcpy(appointment[i].tel, appointment[i+1].tel);
            strcpy(appointment[i].age, appointment[i+1].age);
            strcpy(appointment[i].department, appointment[i+1].department);
            strcpy(appointment[i].doctor, appointment[i+1].doctor);
            strcpy(appointment[i].date, appointment[i+1].date);
            strcpy(appointment[i].weekday, appointment[i+1].weekday);
            strcpy(appointment[i].time, appointment[i+1].time);
        }
        Current_num_appointments--;
        
        FILE* file;
        file = fopen("appointments.txt", "w");
        if(!file)
        {
            printf("Cannot open file \"appointments.txt\"!");
            return 1;
        }
        for(int i = 0; i < Current_num_appointments; i++)
        {
            fprintf(file, "%s\n", appointment[i].app_ID);
            fprintf(file, "%s\n", appointment[i].name);
            fprintf(file, "%s\n", appointment[i].email);
            fprintf(file, "%s\n", appointment[i].tel);
            fprintf(file, "%s\n", appointment[i].age);
            fprintf(file, "%s\n", appointment[i].department);
            fprintf(file, "%s\n", appointment[i].doctor);
            fprintf(file, "%s\n", appointment[i].date);
            fprintf(file, "%s\n", appointment[i].weekday);
            fprintf(file, "%s\n\n", appointment[i].time);
        }
        fclose(file);
    }
    else
        printf("Appointment not found!");
    
    return 0;
}

int load_appointments()
{
    FILE* file;
    file = fopen("appointments.txt", "r");
    if(!file)
    {
        printf("Cannot open file \"appointments.txt\"!");
        return 1;
    }
    char str[100];
    int i = 0; // counter for Appointment struct (9 elements)
    int k = 1;
    while (fgets(str, 100, file) != NULL)
    {
        str[strlen(str)-1] = '\0'; // deleting '\n' at the end of the line
        if (k == 1)
        {
            appointment[i].app_ID = (char*) malloc(4*sizeof(char));
            strcpy(appointment[i].app_ID, str);
        }
        else if (k == 2)
        {
            appointment[i].name = (char*) malloc(30*sizeof(char));
            strcpy(appointment[i].name, str);
        }
        else if (k == 3)
        {
            appointment[i].email = (char*) malloc(30*sizeof(char));
            strcpy(appointment[i].email, str);
        }
        else if (k == 4)
        {
            appointment[i].tel = (char*) malloc(11*sizeof(char));
            strcpy(appointment[i].tel, str);
        }
        else if (k == 5)
        {
            appointment[i].age = (char*) malloc(3*sizeof(char));
            strcpy(appointment[i].age, str);
        }
        else if (k == 6)
        {
            appointment[i].department = (char*) malloc(20*sizeof(char));
            strcpy(appointment[i].department, str);
        }
        else if (k == 7)
        {
            appointment[i].doctor = (char*) malloc(30*sizeof(char));
            strcpy(appointment[i].doctor, str);
        }
        else if (k == 8)
        {
            appointment[i].date = (char*) malloc(10*sizeof(char));
            strcpy(appointment[i].date, str);
        }
        else if (k == 9)
        {
            appointment[i].weekday = (char*) malloc(3*sizeof(char));
            strcpy(appointment[i].weekday, str);
        }
        else if (k == 10)
        {
            appointment[i].time = (char*) malloc(5*sizeof(char));
            strcpy(appointment[i].time, str);
        }
        else {k = 0; i++;}
        k++;
    }
    Current_num_appointments = i;
    fclose(file);
    return 0;
}

int load_doctors()
{
    FILE* file;
    file = fopen("doctors.txt", "r");
    if(!file)
    {
        printf("Cannot open file \"doctors.txt\"!");
        return 1;
    }
    char str[100];
    int i = 0; // counter for department index
    int k = 1; // counter for a department's data
    while (fgets(str, 100, file) != NULL)
    {
        str[strlen(str)-1] = '\0'; // deleting '\n' at the end of the line
        if (k == 1)
        {
            department[i].dep_title = (char*) malloc(20*sizeof(char));
            strcpy(department[i].dep_title, str);
        }
        else if (k == 2)
        {
            department[i].doctors[0].full_name = (char*) malloc(30*sizeof(char));
            strcpy(department[i].doctors[0].full_name, str);
        }
        else if (k == 3)
        {
            department[i].doctors[0].appointment_price = (char*) malloc(4*sizeof(char));
            strcpy(department[i].doctors[0].appointment_price, str);
        }
        else if (k >= 4 && k <=6)
        {
            strncpy(department[i].doctors[0].schedule[(k-4)%3].weekday, str, 3);
            department[i].doctors[0].schedule[(k-4)%3].weekday[3] = '\0';
            strncpy(department[i].doctors[0].schedule[(k-4)%3].session, str + 4, 24);
        }
        else if (k == 7)
        {
            department[i].doctors[1].full_name = (char*) malloc(20*sizeof(char));
            strcpy(department[i].doctors[1].full_name, str);
        }
        else if (k == 8)
        {
            department[i].doctors[1].appointment_price = (char*) malloc(3*sizeof(char));
            strcpy(department[i].doctors[1].appointment_price, str);
        }
        else if (k >= 9 && k <=11)
        {
            strncpy(department[i].doctors[1].schedule[(k-9)%3].weekday, str, 3);
            department[i].doctors[1].schedule[(k-9)%3].weekday[3] = '\0';
            strncpy(department[i].doctors[1].schedule[(k-9)%3].session, str + 4, 24);
        }
        else if (k == 12)
        {
            department[i].doctors[2].full_name = (char*) malloc(20*sizeof(char));
            strcpy(department[i].doctors[2].full_name, str); 
        }
        else if (k == 13)
        {
            department[i].doctors[2].appointment_price = (char*) malloc(3*sizeof(char));
            strcpy(department[i].doctors[2].appointment_price, str);
        }
        else if (k >= 14 && k <=16)
        {
            strncpy(department[i].doctors[2].schedule[(k-14)%3].weekday, str, 3);
            department[i].doctors[2].schedule[(k-14)%3].weekday[3] = '\0';
            strncpy(department[i].doctors[2].schedule[(k-14)%3].session, str + 4, 24);
        }
        else {k = 0; i++;}
        k++;
    }
    fclose(file);
    return 0;
}
