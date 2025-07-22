// Created by Pranav Dubey, Mary Adeeko, Hema Thallapareddy, Luke Marlin - CSCE 3600.001
// Date: 7/21/2025
// Description: File for built-in commands.
#include "myhistory.h"
#include "builtins.h"

int handle_exit(char **args) {
    int status = 0;
    if (args[1]) {
        status = atoi(args[1]);
    }
    exit(status);
    return 0;
}

// Cd Command

int builtin_myhistory(char *line, void (*reexecute)(char *)) {
    return handle_myhistory(line, reexecute);

}