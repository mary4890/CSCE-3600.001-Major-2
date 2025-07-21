//Major 2 Assignment - The Shell and System Calls
//Mary Adeeko, Hema Thallapareddy, Pranav Dubey, Luke Marlin
//CSCE 3600.001
//21 July 2025
//This program will allow users to enter commands in a terminal, it supports
//interactive mode and batch mode.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

#define MAX_ARGS 100
#define MAX_HISORY 100
#define MAX_LINE 512

//Path list for shell
char *list_path[MAX_ARGS];
int count_path = 0;

//Array for history

//Error message
void print_error() //implemented by Mary Adeeko
{
    perror("There is an error\n");
}

//Trimming newline
void trim_newline (char *line) //implemented by Mary Adeeko
{
    size_t len = strlen(line);
    if (len > 0 && line[len - 1] == '\n')
    {
        line[len - 1] = '\0';
    }
}

//History command

//Execute commands
void execute_command(char *line) //implemented by Mary Adeeko
{
    add_history(line);

    char *args[MAX_ARGS];
    char *outfile;

    if (!parse_command(line, args, &outfile)) return;
    if (args[0] == NULL) return;


//Exit

//Cd
else if (strcmp(args[0], "Path") == 0) //implemented by Mary Adeeko
{
    count_path = 0;
    for (int i = 1; args[i] != NULL; ++i)
    {
        list_path[count_path++] = strdup(args[i]);
    }
}

//Path

//Myhistry
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
            perror(There is an error);
            exit(1);
        }
    } else if (argc > 2 )
    {
        perror(There is an error);
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


