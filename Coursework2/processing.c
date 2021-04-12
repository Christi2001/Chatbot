#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "processing.h"

char* process_input(char* string)
{
    chatlog(string);
    char* processed_input = (char*) malloc(200 * sizeof(char));
    int j = 0;
    scanf(" %[^\n]%*c", string);
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

int search_for_department(char* string)
{
    return 0;
}

int search_for_doctor(char* string)
{
    return 0;
}

int search_for_date(char* string, Date date)
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
    fprintf(chatlog, "%s", string);
    fclose(chatlog);
}