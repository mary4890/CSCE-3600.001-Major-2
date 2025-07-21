// Created by Pranav Dubey - CSCE 3600.001
// Date: 7/21/2025
// Description: Defines execute_with_redirection, which handles command execution and optional output redirection.

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h>
#include "redirection.h"

extern char *list_path[];
extern int count_path;

// Executes a command with optional output redirection (if outfile != NULL)
void execute_with_redirection(char **args, char *outfile) {
    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        // If output redirection is requested, open the file and redirect stdout
        if (outfile != NULL) {
            int fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0) {
                perror("open");
                exit(1);
            }
            dup2(fd, STDOUT_FILENO); // Redirect stdout to the file
            close(fd); // Close file descriptor after redirect
        }

        // Try each path in list_path to find the executable
        for (int i = 0; i < count_path; ++i) {
            char fullpath[512];
            snprintf(fullpath, sizeof(fullpath), "%s/%s", list_path[i], args[0]);
            execv(fullpath, args);
        }

        // If execv never succeeds, print shell error
        fprintf(stderr, "There is an error\n");
        exit(1);
    } else if (pid > 0) {
        // Parent process waits for child to complete
        wait(NULL);
    } else {
        // Fork failed
        perror("fork");
    }
}
