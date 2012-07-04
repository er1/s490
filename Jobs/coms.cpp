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

   uint8_t command_type = inputCommand.command_type;
   uint16_t command = inputCommand.command; 
   uint8_t payload_size = inputCommand.payload_size;
   uint8_t * payload_data = inputCommand.payload_data; 
   

   //configure header
   uint8_t header_bytes[8];
   uint8_t header_checksum_A = 0;
   uint8_t header_checksum_B = 0;
   header_bytes[0] = SYNC_CHARACTERS[0];
   header_bytes[1] = SYNC_CHARACTERS[1];
   header_bytes[2] = command_type;        //either COMMAND_TYPE_I or COMMAND_TYPE_O
   header_bytes[3] = command;             //see above op codes
   header_bytes[4] = (payload_size >> 8) & 0xff; //for MSB of payload_size
   header_bytes[5] = payload_size & 0xff; //for LSB of payload_size
   
   //perform header checksum
   for (int i = 0; i< HEADER_SIZE - 2; i++){
      header_checksum_A += header_bytes[i];
      header_checksum_B += header_checksum_A;
      //std::cout << (int) header_checksum_A << "\t" <<  (int) header_checksum_B << std::endl;
   }

   //add checksum to header
   header_bytes[6] = header_checksum_A;
   header_bytes[7] = header_checksum_B;

   //set payload
   uint8_t payload_checksum_A = 0;
   uint8_t payload_checksum_B = 0;


   //perform payload checksum
   for (int i = 0; i< payload_size; i++){
      payload_checksum_A += (int) payload_data[i];
      payload_checksum_B += payload_checksum_A;
      //std::cout << (int) payload_checksum_A << "\t" <<  (int) payload_checksum_B << std::endl;
   }


   //load everything into a single command buffer
   uint8_t command_buffer[HEADER_SIZE + payload_size + 2]; //8 bytes for header, 0 - 255 for paylod, 2 for payload checksums

   for (int i = 0; i < HEADER_SIZE; i++){
      command_buffer[i] = header_bytes[i];
   }

   for (int i = HEADER_SIZE; i < HEADER_SIZE + payload_size; i++){
      command_buffer[i] = payload_data[i - HEADER_SIZE];
   }

   command_buffer[HEADER_SIZE + payload_size] = payload_checksum_A;
   command_buffer[HEADER_SIZE + payload_size + 1] = payload_checksum_B;

   return serialWrite(command_buffer);


}

std::string serialWrite(uint8_t * command){
   int fd; //device handle

   const char *device = "/dev/tty.usbmodem621";
   fd = open(device, O_RDWR | O_NOCTTY | O_NDELAY);
   if(fd == -1) {
     printf( "failed to open port\n" );
   }

   struct termios config;

   if(!isatty(fd)) { std::cout << "Not a TTY" << std::endl; }
   if(tcgetattr(fd, &config) < 0) {std::cout << "Termios structure is broken" << std::endl;}
   //
   // Input flags - Turn off input processing
   // convert break to null byte, no CR to NL translation,
   // no NL to CR translation, don't mark parity errors or breaks
   // no input parity check, don't strip high bit off,
   // no XON/XOFF software flow control
   //
   config.c_iflag &= ~(IGNBRK | BRKINT | ICRNL |
                       INLCR | PARMRK | INPCK | ISTRIP | IXON);
   //
   // Output flags - Turn off output processing
   // no CR to NL translation, no NL to CR-NL translation,
   // no NL to CR translation, no column 0 CR suppression,
   // no Ctrl-D suppression, no fill characters, no case mapping,
   // no local output processing
   //
   // config.c_oflag &= ~(OCRNL | ONLCR | ONLRET |
   //                     ONOCR | ONOEOT| OFILL | OLCUC | OPOST);
   config.c_oflag = 0;
   //
   // No line processing:
   // echo off, echo newline off, canonical mode off, 
   // extended input processing off, signal chars off
   //
   config.c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN | ISIG);
   //
   // Turn off character processing
   // clear current char size mask, no parity checking,
   // no output processing, force 8 bit input
   //
   config.c_cflag &= ~(CSIZE | PARENB);
   config.c_cflag |= CS8;
   //
   // One input byte is enough to return from read()
   // Inter-character timer off
   //
   config.c_cc[VMIN]  = 1;
   config.c_cc[VTIME] = 0;
   //
   // Communication speed (simple version, using the predefined
   // constants)
   //
   if(cfsetispeed(&config, B9600) < 0 || cfsetospeed(&config, B9600) < 0) {
       std::cout << "Speed is messed up" << std::endl;
   }
   //
   // Finally, apply the configuration
   //
   if(tcsetattr(fd, TCSAFLUSH, &config) < 0) { std::cout << "Applied Configuration is broken" << std::endl;}

   char c ='D';
   write(fd,&command,1);

   // for (int i = 0; i < command[5]+10; i++){
   //    std::cout << "BIN" << i << ": " << std::setw(8) << std::bitset<CHAR_BIT>(command[i]);
   //    std::cout << "\t\t\tHex" << i << ": " << std::setw(8) << std::hex << (unsigned int) command[i];
   //    std::cout << "\t\t\tDec" << i << ": " << std::setw(10) << std::dec << (unsigned int) command[i];
   //    std::cout << "\t\t\tASCII" << i << ": " << command[i] << std::endl;
   // }


   close(fd);

   return "successful";
}

