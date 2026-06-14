#include<stdlib.h>

#include "../include/environment.h"

extern char **environ;

void expand_variables(char *argv[]) {
    for (int i = 0; argv[i] != NULL; i++) {
        if (argv[i][0] == '$') {
            char *var_name = argv[i] + 1;
            char *value = getenv(var_name);

            if (value != NULL)
             {
                argv[i] = value;
            } 
            else {
                argv[i] = "";
            }
        }
    }
}
