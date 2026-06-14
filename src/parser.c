#include<stdio.h>
#include<string.h>

void parse_input(char *input, char *argv[]){
    int i=0;
    char *token = strtok(input," ");

    while(token != NULL) {
    
        argv[i]= token;
        i++;
        token = strtok(NULL," ");
    }
    argv[i] = NULL;
}