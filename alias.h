#ifndef ALIAS_H
#define ALIAS_H

#define MAX_ALIAS 50
#define MAX_ALIAS_NAME 50
#define MAX_ALIAS_COMMAND 100

typedef struct {
    char name[MAX_ALIAS_NAME];
    char command[MAX_ALIAS_COMMAND];
} Alias;

void set_alias(char *name, char *command);
char* get_alias_command(const char *name);
void handle_alias(char **args);

#endif
