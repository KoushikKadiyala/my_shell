#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#include "../include/executor.h"
#include "../include/launcher.h"
#include "../include/process.h"



void execute_command(char *argv[])
{
    int pipe_index = -1;

    for (int i = 0; argv[i] != NULL; i++)
    {
        if (strcmp(argv[i], "|") == 0)
        {
            pipe_index = i;
            break;
        }
    }

    if (pipe_index == -1)
    {
        execute_simple_command(argv);
        return;
    }

    if (pipe_index == 0)
    {
        printf("Syntax error before pipe\n");
        return;
    }

    if (argv[pipe_index + 1] == NULL)
    {
        printf("Syntax error after pipe\n");
        return;
    }

    argv[pipe_index] = NULL;

    char **left = argv;
    char **right = &argv[pipe_index + 1];

    execute_pipe_command(left, right);
}
