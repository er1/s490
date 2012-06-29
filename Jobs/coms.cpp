/*
   Copyright 2012 Space Concordia
   Author: Nick Sweet
   Subsystem Lead: Tiago Leao

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

   The following lists the jobs specific to the Communications System on ConSat-1.
*/

#include "coms.h"

std::string command_transceiver(Transceiver_Command inputCommand){ 

   unsigned char command_type = inputCommand.command_type;
   unsigned int command = inputCommand.command; 
   unsigned char * payload_data = inputCommand.payload_data; 
   unsigned int payload_size = inputCommand.payload_size;

   //configure header
   unsigned char header_bytes[8];
   unsigned char header_checksum_A = 0;
   unsigned char header_checksum_B = 0;
   header_bytes[0] = SYNC_CHARACTERS[0];
   header_bytes[1] = SYNC_CHARACTERS[1];
   header_bytes[2] = command_type;        //either COMMAND_TYPE_I or COMMAND_TYPE_O
   header_bytes[3] = command;             //see above op codes
   header_bytes[4] = payload_size & 0xff; //for first byte of payload_size
   header_bytes[5] = (payload_size >> 8) & 0xff;

   //perform header checksum
   for (int i = 0; i< HEADER_SIZE - 2; i++){
      header_checksum_A += header_bytes[i];
      header_checksum_B += header_checksum_A;
   }

   //add checksum to header
   header_bytes[6] = header_checksum_A;
   header_bytes[7] = header_checksum_B;

   //set payload
   unsigned char payload_checksum_A = 0;
   unsigned char payload_checksum_B = 0;


   //perform payload checksum
   for (int i = 0; i< payload_size; i++){
      payload_checksum_A += payload_data[i];
      payload_checksum_B += payload_checksum_A;
   }

   //load everything into a single command buffer
   unsigned char command_buffer[HEADER_SIZE + payload_size + 2]; //8 bytes for header, 0 - 255 for paylod, 2 for payload checksums

   for (int i = 0; i < HEADER_SIZE; i++){
      command_buffer[i] = header_bytes[i];
   }

   for (int i = HEADER_SIZE; i < HEADER_SIZE + payload_size; i++){
      command_buffer[i] = payload_data[i];
   }
   command_buffer[HEADER_SIZE + payload_size] = payload_checksum_A;
   command_buffer[HEADER_SIZE + payload_size + 1] = payload_checksum_B;

   //Serial Communication
   //start serial communication
   //send data
   //receive return message

   std::string received;

   return received;
}

