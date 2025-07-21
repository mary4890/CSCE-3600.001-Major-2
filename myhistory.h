// myhistory.h

#ifndef MYHISTORY_H
#define MYHISTORY_H

void add_history(const char *line);
void show_history();
void clear_history();
void execute_history(int index, void (*reexecute)(char *));
int handle_myhistory(char *line, void (*reexecute)(char *));

#endif
