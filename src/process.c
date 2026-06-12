#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#include "../include/process.h"
#include "../include/launcher.h"

void execute_simple_command(char *argv[])
{
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork");
        return;
    }

    if (pid == 0)
    {
        launch_process(argv);
    }

    waitpid(pid, NULL, 0);
}

void execute_pipe_command(char *left_cmd[],
                          char *right_cmd[])
{
    int pipefd[2];

    if (pipe(pipefd) < 0)
    {
        perror("pipe");
        return;
    }

    pid_t pid1 = fork();

    if (pid1 == 0)
    {
        dup2(pipefd[1], STDOUT_FILENO);

        close(pipefd[0]);
        close(pipefd[1]);

        launch_process(left_cmd);
    }

    pid_t pid2 = fork();

    if (pid2 == 0)
    {
        dup2(pipefd[0], STDIN_FILENO);

        close(pipefd[0]);
        close(pipefd[1]);

        launch_process(right_cmd);
    }

    close(pipefd[0]);
    close(pipefd[1]);

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}
