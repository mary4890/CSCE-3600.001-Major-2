# CSCE 3600.001 Major 2 Assignment: The Shell and System Calls
# Mary Adeeko, Hema Thallapareddy, Pranav Dubey, Luke Marlin
# 21 July 2025
# Makefile for compiling the custom shell project

# Compiler and flags - Implemented by Mary Adeeko
CC = gcc
CFLAGS = -Wall -g

# Object files for all source modules - Implemented by Pranav Dubey
OBJS = newshell.o parser.o path.o redirection.o builtins.o alias.o pipe.o signal_handler.o myhistory.o

# Default target: build the shell executable - Implemented by Pranav Dubey
all: newshell

# Link object files to produce final executable - Implemented by Pranav Dubey
newshell: $(OBJS)
	$(CC) $(CFLAGS) -o newshell $(OBJS)

# Compilation rules for each source file - Implemented by Pranav Dubey
newshell.o: newshell.c parser.h path.h redirection.h builtins.h alias.h pipe.h signal_handler.h
parser.o: parser.c parser.h
path.o: path.c path.h
redirection.o: redirection.c redirection.h
builtins.o: builtins.c builtins.h
alias.o: alias.c alias.h
pipe.o: pipe.c pipe.h
signal_handler.o: signal_handler.c signal_handler.h
myhistory.o: myhistory.c myhistory.h


# Clean target to remove compiled files - Implemented by Pranav Dubey
clean:
	rm -f *.o newshell
