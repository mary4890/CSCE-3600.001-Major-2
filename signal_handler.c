// Created by Hema Thallapareddy - CSCE 3600.001
// Date: 7/21/2025
// Description: Implements signal handling behavior for the shell and its child processes.

#include <signal.h>
#include "signal_handler.h"

void setup_shell_signals() {
    signal(SIGINT, SIG_IGN);   // Ignore Ctrl-C
    signal(SIGTSTP, SIG_IGN);  // Ignore Ctrl-Z
}

void setup_child_signals() {
    signal(SIGINT, SIG_DFL);   
    signal(SIGTSTP, SIG_DFL);  
}
