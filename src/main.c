#include "core/shell.h"
#include <string.h>
#include <utility.h>

#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

// On SIGINT, flush terminal input and print PS1
void handle_sigint(int signal) {
    reset_shell();
}

void setup_signal_handlers() {
    struct sigaction sig_action = {0};
    // Set the handler to be called on SIGINT
    sig_action.sa_handler = handle_sigint;
    // unset all flags on sigaction struct
    sigemptyset(&sig_action.sa_mask);

    // Bind the sigaction struct to the SIGINT signal
    if (sigaction(SIGINT, &sig_action, NULL) == -1) {
        perror("sigaction error");
    }
}

// General function to do things before the shell is started
void initialize_shell() {
    char path[INITIAL_BUFSIZE_BIG];
    signed long length = readlink("/proc/self/exe", path, INITIAL_BUFSIZE_BIG);
    if (length == -1) {
        log_error_with_exit("Could not read executable name");
    }

    path[length] = '\0';
    // set the SHELL env-var to the path of the current executable
    setenv("SHELL", path, true);
}

int main() {
    setup_signal_handlers();
    initialize_shell();
    atexit(cleanup);

    while (true) {
        create_prompt();
    }

    return 0;
}
