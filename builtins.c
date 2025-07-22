// Created by Pranav Dubey, Mary Adeeko, Hema Thallapareddy, Luke Marlin - CSCE 3600.001
// Date: 7/21/2025
// Description: File for built-in commands.
#include "myhistory.h"
#include "builtins.h"

// Exit command

// Cd Command

int builtin_myhistory(char *line, void (*reexecute)(char *)) {
    return handle_myhistory(line, reexecute);
}
