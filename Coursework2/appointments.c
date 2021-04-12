#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "appointments.h"

char* current_day()
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("now: %s %02d-%02d-%d %02d:%02d:%02d\n", weekday[tm.tm_wday], tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
    return weekday[tm.tm_wday];

    // return NULL;
}

long int string_to_sec(char* str)
{
    struct tm t1;
    strptime(str, "%d.%m.%Y", &t1);
    time_t t = mktime(&t1);
    return t;
}

struct tm string_to_tm(char* str)
{
    struct tm t1;
    strptime(str, "%d.%m.%Y", &t1);
    return t1;
}

int check_availability(char* date, char* time, char* doc_name)
{
    struct tm t1 = string_to_tm(date);
    char* wd;
    strcpy(wd, weekday[t1.tm_wday]);
    for(int a = 0; a < 10; a++)
        for(int b = 0; b < 3; b++)
            if(strcmp(doc_name, department[a].doctors[b].full_name) == 0)
            {
            for(int i = 0; i < Current_num_appointments; i++)
                if(strcmp(department[a].doctors[b].full_name, appointment[i].doctor) == 0 && strcmp(date, appointment[i].date) == 0 && strcmp(time, appointment[i].time) == 0)
                    return 1;

            for(int i = 0; i < 3; i++)
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

// int doctor_availability(char* date, char* doc)
// {
//     struct tm t1 = string_to_tm(date);
//     char* wd;
//     strcpy(wd, weekday[t1.tm_wday]);
//     Schedule sch;
//     for(int a = 0; a < 10; a++)
//         for(int b = 0; b < 3; b++)
//             if(strcmp(doc, department[a].doctors[b].full_name) == 0)
//             {
//                 for(int c = 0; c < 3; c++)
//                     if(strcmp(wd, department[a].doctors[b].schedule[c].weekday) == 0)
//                     {
//                         strcpy(sch.weekday, department[a].doctors[b].schedule[c].weekday);
//                         strcpy(sch.session, department[a].doctors[b].schedule[c].session);
//                         break;
//                     }
//                     else
//                         return 1;
//             }

//                 for(int i = 0; i < Current_num_appointments; i++)
//                 if(strcmp(department[a].doctors[b].full_name, appointment[i].doctor) == 0)
//     for(int i = 0; i < 24; i++)
// }

Schedule department_availability(char* dep)
{
    Schedule sch[3];
    for(int a = 0; a < 10; a++)
        if(strcmp(dep, department[a].dep_title) == 0)
        {
            
        }
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
    fprintf(file, "%i\n", app.app_ID);
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
            department[i].doctors[0].appointment_price = (char*) malloc(3*sizeof(char));
            strcpy(department[i].doctors[0].appointment_price, str);
        }
        else if (k >= 4 && k <=6)
        {
            strncpy(department[i].doctors[0].schedule[(k-3)%3].weekday, str, 3);
            strncpy(department[i].doctors[0].schedule[(k-3)%3].session, str + 4, 24);
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
            strncpy(department[i].doctors[1].schedule[(k-7)%3].weekday, str, 3);
            strncpy(department[i].doctors[1].schedule[(k-7)%3].session, str + 4, 24);
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
            strncpy(department[i].doctors[2].schedule[(k-11)%3].weekday, str, 3);
            strncpy(department[i].doctors[2].schedule[(k-11)%3].session, str + 4, 24);
        }
        else {k = 0; i++;}
        k++;
    }
    fclose(file);
    return 0;
}


int main()
{
    int a;
    a = load_appointments();
    if (a != 0)
        exit(1);
    
    for(int i = 0; i < Current_num_appointments; i++)
    {
        printf("%s\n", appointment[i].app_ID);
        printf("%s\n", appointment[i].name);
        printf("%s\n", appointment[i].email);
        printf("%s\n", appointment[i].tel);
        printf("%s\n", appointment[i].age);
        printf("%s\n", appointment[i].department);
        printf("%s\n", appointment[i].doctor);
        printf("%s\n", appointment[i].date);
        printf("%s\n", appointment[i].weekday);
        printf("%s\n\n", appointment[i].time);
    }
    printf("%i\n", Current_num_appointments);
    // Appointment app;
    // app.app_ID = (char*) malloc(4*sizeof(char));
    // // app.app_ID = NULL;
    // app.name = (char*) malloc(30*sizeof(char));
    // app.email = (char*) malloc(30*sizeof(char));
    // app.tel = (char*) malloc(11*sizeof(char));
    // app.age = (char*) malloc(3*sizeof(char));
    // app.department = (char*) malloc(20*sizeof(char));
    // app.doctor = (char*) malloc(20*sizeof(char));
    // app.date = (char*) malloc(11*sizeof(char));
    // app.weekday = (char*) malloc(3*sizeof(char));
    // app.time = (char*) malloc(5*sizeof(char));

    // printf("Please enter your details: \n");
    // scanf(" %[^\n]%*c", app.name);
    // // printf("%s\n", app.name);
    // scanf("%s", app.email);
    // // printf("%s\n", app.email);
    // scanf("%s", app.tel);
    // scanf("%s", app.age);
    // scanf("%s", app.department);
    // scanf(" %[^\n]%*c", app.doctor);
    // scanf("%s", app.date);
    // scanf("%s", app.weekday);
    // scanf("%s", app.time);
    // save_appointment(app);

    // scanf("%s", app.app_ID);
    // scanf(" %[^\n]%*c", app.name);
    // scanf("%s", app.tel);
    // scanf(" %[^\n]%*c", app.doctor);
    // scanf("%s", app.date);
    // scanf("%s", app.time);
    // app.name = "Christian Pustianu";
    // app.tel = "0735851024";
    // app.doctor = "mohamed webster";
    // app.date = "06.04.2021";
    // app.time = "13:30";

    // printf("%s\n", app.app_ID);
    // printf("%s\n", app.name);
    // printf("%s\n", app.email);
    // printf("%s\n", app.tel);
    // printf("%s\n", app.age);
    // printf("%s\n", app.department);
    // printf("%s\n", app.doctor);
    // printf("%s\n", app.date);
    // printf("%s\n", app.weekday);
    // printf("%s\n", app.time);
    // cancel_appointment(app);
    int b;
    b = load_doctors();
    printf("\nLoading doctors...\n");
    if (b != 0)
        exit(1);
    int c = check_availability("16.04.2021", "Fri", "09:30", "shiv boyce");
    printf("%i", c);
}