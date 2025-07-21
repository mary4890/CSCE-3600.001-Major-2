# CSCE 3600.001 Major 2 Assignment: The Shell and System Calls
# Mary Adeeko, Hema Thallapareddy, Pranav Dubey, Luke Marlin
# 21 July 2025
# Makefile

CC = gcc
CFLAGS = -Wall -g

all: newshell
newshell: newshell.c
  $(CC) $(CFLAGS) -o newshell newshell.c
clean:
  rm -f newshell
