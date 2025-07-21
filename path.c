// Created by Pranav Dubey - CSCE 3600.001
// Date: 7/21/2025
// Description: Defines set_path function to update list of executable search paths.

#include <string.h>
#include <stdlib.h>
#include "path.h"

// External path list defined in newshell.c
extern char *list_path[];
extern int count_path;

// Updates the global list_path array with provided directories
void set_path(char **args) {
    count_path = 0;
    for (int i = 1; args[i] != NULL; ++i) {
        list_path[count_path++] = strdup(args[i]);
    }
}
