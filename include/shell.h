#ifndef SHELL_H
#define SHELL_H

// Reset terminal input buffer (used in SIGINT handling)
void reset_shell();

// Reads input from the user
char *read_input();

// Main shell loop
void create_prompt();

#endif
