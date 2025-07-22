// myhistory.c
//Luke Marlin
// csce 3600
// Handles the 'myhistory' built-in command:
// - Lists up to 20 recent commands
// - Clears history with '-c'
// - Re-executes a past command with '-e <index>'


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myhistory.h"

#define MAX_HISTORY 20

static char *history[MAX_HISTORY];
static int count = 0;
static int start = 0;

void add_history(const char *line) {
    if (!line || strlen(line) <= 1 || strncmp(line, "myhistory", 9) == 0) return;

    char *clean = strdup(line);
    if (!clean) return;

    int index = (start + count) % MAX_HISTORY;

    if (count == MAX_HISTORY) {
        free(history[start]);
        history[start] = clean;
        start = (start + 1) % MAX_HISTORY;
    } else {
        history[index] = clean;
        count++;
    }
}

void show_history() {
    for (int i = 0; i < count; i++) {
        int idx = (start + i) % MAX_HISTORY;
        printf("%d: %s\n", i, history[idx]);
    }
}

void clear_history() {
    for (int i = 0; i < count; i++) {
        int idx = (start + i) % MAX_HISTORY;
        free(history[idx]);
    }
    count = 0;
    start = 0;
}

void execute_history(int index, void (*reexecute)(char *)) {
    if (index < 0 || index >= count) {
        fprintf(stderr, "Invalid history index\n");
        return;
    }
    int idx = (start + index) % MAX_HISTORY;
    printf("Executing: %s\n", history[idx]);
    reexecute(history[idx]);  // Pass to shell's own execution
}

int handle_myhistory(char *line, void (*reexecute)(char *)) {
    char *token = strtok(line, " \t");
    token = strtok(NULL, " \t"); // Get option

    if (!token) {
        show_history();
        return 1;
    }

    if (strcmp(token, "-c") == 0) {
        clear_history();
        return 1;
    }

    if (strcmp(token, "-e") == 0) {
        char *num = strtok(NULL, " \t");
        if (!num) {
            fprintf(stderr, "Usage: myhistory -e <index>\n");
            return 1;
        }
        int index = atoi(num);
        execute_history(index, reexecute);
        return 1;
    }

    fprintf(stderr, "Invalid myhistory usage\n");
    return 1;
}
