//pipe.c
//Mary Adeeko, mya0051, Group 3
//CSCE 3600.001
//21 July 2025
//Implements a way to handle pipelining of commands connected by pipe operator.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

#define MAX_ARGS 100
#define MAX_CMDS 3

//Split pipeline into commands and excute w pipes
void handle_pipeline(char *line)
{
    char *commands[MAX_CMDS];
    int ncmds = 0;

    //Split lines
    commands[ncmds++] = strtok(line, "|");
    while (ncmds < MAX_CMDS && (commands[ncmds] = strtok(NULL, "|")) != NULL)
    {
        ncmds++;
    }

    int pipefds[2 * (ncmds - 1)];

    //Make new pipes
    for (int i = 0; i < ncmds - 1; i++)
    {
        if (pipe(pipefds + i*2) < 0)
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < ncmds; i++)
    {
        pid_t pid = fork();
        if (pid == 0)
        {
            //Child process - if not first commannd, get input from prev pipe
            if (i != 0)
            {
                dup2(pipefds[(i - 1) * 2], STDIN_FILENO);
            }

            //If not last command, output next pipe
            if (i != ncmds - 1)
            {
                dup2(pipefds[i * 2 + 1], STDOUT_FILENO);
            }

            //Close pipe fds for child
            for (int j = 0; j < 2 * (ncmds - 1); j++)
            {
                close(pipefds[j]);
            }

            //Parse command for args array
            char *args[MAX_ARGS];
            int argi = 0;
            char *token = strtok(commands[i], " \t\n");
            while (token != NULL && argi < MAX_ARGS - 1)
            {
                args[argi++] = token;
                token = strtok(NULL, " \t\n");
            }
            args[argi] = NULL;

            //Execute the command
            execvp(args[0], args);
            perror("execvp");
            exit(EXIT_FAILURE);
        } else if (pid < 0)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
    }

    //Close pipe fds w paren
    for (int i = 0; i < 2 * (ncmds - 1); i++)
    {
        close(pipefds[i]);
    }

    //Parent must wait for children
    for (int i = 0; i < ncmds; i++)
    {
        wait(NULL);
    }
}
