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

#define HE_UART_TX 17
#define HE_UART_RX 18
#define COMMAND_TYPE_I 0x10      //For data entering the radio
#define COMMAND_TYPE_O 0x20      //For data leaving the radio
#define HEADER_SIZE 8

const double SNR_LIMIT = 1; //in dBm ||FIGURE OUT WHAT THE LIMIT IS||
const unsigned char SYNC_CHARACTERS[2] = {'H','e'};

struct Transceiver_Command{
unsigned char command_type;
unsigned int command;
unsigned char * payload_data;
unsigned int payload_size;
};


//COMMAND_TYPE_I Op Codes
#define I_NO_OP 0x1001           //Simply increment command processing counter
#define I_RESET 0x1002           //Reset radio processors and systems
#define I_TRANSMIT 0x1003        //Send n bytes to radio
#define I_GET_CONFIG 0x1004      //Get radio configuration
#define I_SET_CONFIG 0x1005      //Set radio configuration
#define I_BUFFER_QUERY 0x1006    //Request # of buffers in transmission queue
#define I_TELEMETRY 0x100A       //query a telemetry frame

//COMMAND_TYPE_O Op Codes
#define O_NO_OP 0x2001           //Acknowledge No-Op
#define O_RESET 0x2002           //Acknowledge radio processors and systems reset
#define O_TRANSMIT 0x2003        //Acknowledge valid transmit command
#define O_GET_CONFIG 0x2004      //Response to read radio configuration (returns struct of radio config)
#define O_SET_CONFIG 0x2005      //Acknowledge radio configuration set
#define O_BUFFER_QUERY 0x2006    //Response to buffer query (returns depth of transmission buffer)
#define O_TELEMETRY 0x200A       //query telemetry points


/*Subsystem Check*/
   //check link margin parameters
   //check related sensors (thermistors, ammeters(?)) |||talk to Ty and Shawn about sensors|||



/*Enable Beacon Mode*/
   //Establish the Beacon message
   //Translate the Beacon Message to Morse Code
   //Define the number of beacon pulses to transmit
   //Transmit the morse code beacon by pulsating the transmit power
   //End Beacon mode as per defined beacon number


/*Change Baud Rate*/ //|||commanded from the ground station|||
   //Poll last established link margin data
   //Only if SNR is above SNR_LIMIT
   //Change the transceiver transmit bitrate


/*Prepare Data for Transmission*/
   //load prepared data from C&DH into RAM
   //||LOOK INTO PACKET TRANSMISSION FOR TRANSCEIVER||
   //Configure transceiver registers (e.g. Power Level)
int command_transceiver(Transceiver_Command inputCommand){ 

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
}


/*Establish Link*/
   //listen for ground station link
   //handshake


/*Transmit*/
   //transmit data based on priority
   //resend items on resend list
   //mark surplus data for next transmission

/*Receive*/
   //listen for resend list
   //update knowledge items (i.e. position lookup table)



