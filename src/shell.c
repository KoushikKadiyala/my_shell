#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include <readline/readline.h>
#include <readline/history.h>

#include "../include/colours.h"
#include "../include/shell.h"
#include "../include/parser.h"
#include "../include/executor.h"
#include "../include/builtins.h"

void start_shell()
{
    char *argv[64];

    while (1)
    {
        char cwd[1024];
        char prompt[1200];

        if (getcwd(cwd, sizeof(cwd)) != NULL)
        {
            snprintf(
                prompt,
                sizeof(prompt),
                BLUE BOLD "%s " RESET RED BOLD "> " RESET,
                cwd
            );
        }
        else
        {
            strcpy(prompt, "$ ");
        }

        char *input = readline(prompt);

        if (input == NULL)
        {
            printf("\nGoodbye!\n");
            break;
        }

        if (strlen(input) > 0)
        {
            add_history(input);
        }

        parse_input(input, argv);

        if (argv[0] == NULL)
        {
            free(input);
            continue;
        }

        if (strcmp(argv[0], "exit") == 0)
        {
            free(input);
            printf("Goodbye!\n");
            break;
        }

        if (handle_builtin(argv))
        {
            free(input);
            continue;
        }

        execute_command(argv);

        free(input);
    }
}