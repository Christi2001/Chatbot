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
    char* input = (char*) malloc(200 * sizeof(char));
    char* processed_input = (char*) malloc(200 * sizeof(char));
    char* reply = (char*) malloc(200* sizeof(char));

    strcpy(reply, say_introduction());
    chatlog(reply);
    scanf(" %[^\n]%*c", input);
    processed_input = process_input(input);

    while(1)
    {
    chatlog(reply);
    scanf(" %[^\n]%*c", input);
    processed_input = process_input(input);
    }

    // char* ptr = NULL;
    // char* usr_input = read_input();
    // ptr = strstr(usr_input, "hello");
    // if(ptr != NULL) printf("Found!");
    // else printf("Not found!");
    // printf("\n%s\n", usr_input);
    
    // char* usr_input2 = read_input();
    // ptr = strstr(usr_input2, "hello");
    // if(ptr != NULL) printf("Found!");
    // else printf("Not found!");
    // printf("\n%s\n", usr_input2);

    return 0;
}