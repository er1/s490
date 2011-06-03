#ifndef _COMM_H_
#define _COMM_H_

// Libs 
#include <stdio.h>

/** The buffer used for receiving stuff. */
char* comms_buffer; 

void comms_exec();

short comms_OK(); 
short comms_send();
short comms_receive();
short comms_check();

#endif
