#ifndef SHELL_H
#define SHELL_H

#include <string.h>

// Reset terminal input buffer (used in SIGINT handling)
void reset_shell();

// Main shell loop
void create_prompt();

void set_env_field(char *special_field, size_t special_field_size, char *env_var);

void execute_input();

#endif
