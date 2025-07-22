// Created by Pranav Dubey, Mary Adeeko, Hema Thallapareddy, Luke Marlin - CSCE 3600.001
// Date: 7/21/2025
// Description: Header for built-in shell command declarations

#ifndef BUILTINS_H
#define BUILTINS_H
#include "myhistory.h"
#include "alias.h"


// Exit command handler

// Cd command handler

int builtin_myhistory(char *line, void (*reexecute)(char *));

// Alias-related functions
void handle_alias(char **args);
char* get_alias_command(const char *name);
void set_alias(char *name, char *command);


#endif
