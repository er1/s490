#include "log.h"

/** This will store a small log that can be sent back to earth in order for examining to 
make sure that everything is going alright. */

/** The log's filename. */
char log_filename[] = "LOG.txt"; 

/** The file's maximum size to reach.
TODO - discuss about this before implementing it. 
0 should denote unlimited. */
uint32_t log_max_file_size = 0; 

/** Log the message to the file. */
void log_message(char* msg) {
  FILE* f; 
  f = fopen(log_filename, "a+");
  fprintf(f, msg); 
  fclose(f); 
}

/** Completely erase the logfile. This will probably be done each time a connection to 
earth is established and the base successfully retrieves the log. */
void log_clear() {
  FILE* f; 
  f = fopen(log_filename, "w"); 
  fclose(f); 
}
