// Created by Pranav Dubey - CSCE 3600.001
// Date: 7/21/2025
// Description: Implements the parse_command function, which takes a command line string and splits it into arguments (stores them in the 'args' array)

#include <string.h>
#include <stdlib.h>
#include "parser.h"

#define MAX_ARGS 100

int parse_command(char *line, char **args, char **outfile) {
    *outfile = NULL;

    int i = 0;
    char *token = strtok(line, " ");

    while (token != NULL && i < MAX_ARGS - 1) {
        if (strcmp(token, ">") == 0) {
            // Handles output redirection: stores the next token as the output file
            token = strtok(NULL, " ");
            if (token == NULL) return 0;  // For if no file is provided after '>'
            *outfile = token;
        } else {
            args[i++] = token;
        }
        token = strtok(NULL, " ");
    }

    args[i] = NULL;  // Null-terminate the 'args' array
    return 1;
}