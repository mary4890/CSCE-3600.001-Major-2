//Major 2 Assignment - The Shell and System Calls
//Mary Adeeko, Hema Thallapareddy, Pranav Dubey, Luke Marlin
//CSCE 3600.001
//21 July 2025
//Description: This program will allow users to enter commands in a terminal, it supports interactive mode and batch mode.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "builtins.h"
#include "path.h"
#include "redirection.h"
#include "parser.h"
#include "pipe.h"

#define MAX_ARGS 100
#define MAX_HISTORY 100
#define MAX_LINE 512

// Path list for shell
char *list_path[MAX_ARGS];
int count_path = 0;

//Error message
void print_error() //implemented by Pranav Dubey
{
    fprintf(stderr, "There is an error\n");
}

// Trimming newline
void trim_newline(char *line) // implemented by Mary Adeeko
{
    size_t len = strlen(line);
    if (len > 0 && line[len - 1] == '\n')
    {
        line[len - 1] = '\0';
    }
}

//Execute commands
void execute_command(char *line) // Implemented by Pranav Dubey
{
    // add_history(line); // Needs to be implemented in builtsin.c first before uncommenting this, otherwise program won't run on tests

    char *args[MAX_ARGS];
    char *outfile;

    if (!parse_command(line, args, &outfile)) {
        print_error();
        return;
    }
    if (args[0] == NULL) return;

    // *Built-in Commands*

    // Exit

    // Cd - Implemented by Mary Adeeko
    if (strcmp(args[0], "cd") == 0)
{
    if (args[1] == NULL)
    {
        char *home = getenv("HOME");
        if (home == NULL || chdir(home) !=0 )
        {
            print_error();
        }
    }
    else
    {
        if (chdir(args[1]) != 0)
        {
            print_error();
        }
    }
    return;
}

    // Myhistory

    // Path - Implemented by Pranav Dubey
    else if (strcmp(args[0], "path") == 0)
    {
        set_path(args);
        return;
    }

    // *Advanced Features*

    // Signal handling

    // Pipelining

    // Alias

    // Redirection - Implemented by Pranav Dubey
    execute_with_redirection(args, outfile);
}



//Main
int main(int argc, char *argv[]) //implemented by Mary Adeeko
{
    list_path[0] = "/bin";
    count_path = 1;

    FILE *input = stdin;
    char line [MAX_LINE];

    if (argc == 2)
    {
        input = fopen(argv[1], "r");
        if (!input)
        {
            print_error();
            exit(1);
        }
    } else if (argc > 2 )
    {
        print_error();
        exit(1);
    }
    while (1)
    {
        if (input == stdin) printf("Newshell> ");
        if (fgets(line, MAX_LINE, input) == NULL) break;
        trim_newline(line);

        char *cmd = strtok(line, ";");
        while (cmd != NULL)
        {
            execute_command(cmd);
            cmd = strtok(NULL, ";");
        }
    }
    return 0;
}


