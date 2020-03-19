#ifndef CHECK_COMMAND_H
#define CHECK_COMMAND_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

#define MIN_PROCESS  2
#define MAX_PROCESS  8
#define SIZE_MAX_ 1024 

/**
 * Check command line
 * @return boolean
 */
bool is_command_valid(char **argv);

#endif