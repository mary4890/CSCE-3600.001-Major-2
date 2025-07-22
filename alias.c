#include <stdio.h>
#include <string.h>
#include "alias.h"

static Alias aliases[MAX_ALIAS];
static int alias_count = 0;

void set_alias(char *name, char *command) {
    for (int i = 0; i < alias_count; i++) {
        if (strcmp(aliases[i].name, name) == 0) {
            strcpy(aliases[i].command, command);
            return;
        }
    }
    if (alias_count < MAX_ALIAS) {
        strcpy(aliases[alias_count].name, name);
        strcpy(aliases[alias_count].command, command);
        alias_count++;
    } else {
        fprintf(stderr, "Alias limit reached\n");
    }
}

char* get_alias_command(const char *name) {
    for (int i = 0; i < alias_count; i++) {
        if (strcmp(aliases[i].name, name) == 0) {
            return aliases[i].command;
        }
    }
    return NULL;
}

void handle_alias(char **args) {
    if (args[1] == NULL) {
        // List all aliases
        for (int i = 0; i < alias_count; i++) {
            printf("%s='%s'\n", aliases[i].name, aliases[i].command);
        }
    } else {
        // Expect format: alias name='command'
        char *equal_sign = strchr(args[1], '=');
        if (equal_sign == NULL) {
            fprintf(stderr, "Invalid alias format\n");
            return;
        }

        *equal_sign = '\0';
        char *name = args[1];
        char *command = equal_sign + 1;

        // Remove surrounding quotes if present
        if (command[0] == '\'') command++;
        int len = strlen(command);
        if (command[len - 1] == '\'') command[len - 1] = '\0';

        set_alias(name, command);
    }
}
