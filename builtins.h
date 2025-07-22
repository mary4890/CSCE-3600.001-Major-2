// Created by Pranav Dubey, Mary Adeeko, Hema Thallapareddy, Luke Marlin - CSCE 3600.001
// Date: 7/21/2025
// Description: Header for built-in shell command declarations

#ifndef BUILTINS_H
#define BUILTINS_H
#include "myhistory.h"


int handle_exit(char **args);

// Cd command handler

int builtin_myhistory(char *line, void (*reexecute)(char *));
int builtin_alias(char *line);


#endif
