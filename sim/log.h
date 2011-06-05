#ifndef LOG_H
#define LOG_H

#include <stdint.h>
#include <stdio.h>

void log_message(char*); 

void log_clear(); 

uint32_t log_check_file_size();

#endif 

