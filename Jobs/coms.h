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

#include <string>
#include <iostream>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <bitset>
#include <iomanip>



#define HE_UART_TX 17
#define HE_UART_RX 18
#define COMMAND_TYPE_I 0x10      //For data entering the radio
#define COMMAND_TYPE_O 0x20      //For data leaving the radio
#define HEADER_SIZE 8

const double SNR_LIMIT = 1; //in dBm ||FIGURE OUT WHAT THE LIMIT IS||
const char SYNC_CHARACTERS[2] = {'H','e'};

typedef struct {
   uint8_t command_type;
   uint16_t command;
   uint8_t * payload_data;
   uint16_t payload_size;
} Transceiver_Command;

typedef struct {
   uint8_t radio_interface_mode;//Radio Interface mode (default AX.25 = 0x01) 
   uint32_t radio_time;//Radio Time (default 0x0000)
   uint8_t interface_baud_rate;//Radio Interface Baud Rate (default 9600=0x03) 
   uint8_t tx_rf_baud_rate; //Radio TX RF Baud Rate (default 9600=0x02) 
   uint8_t rx_rf_baud_rate; //Radio RX RF Baud Rate (default 9600=0x02) 
   uint8_t rx_buff_size; //Rx Buffer Size (default 0x06)
   uint8_t tx_buff_size; //Tx Buffer Size (default 0x04)
   uint8_t tx_power_amp_level; //Tx Power Amp level (default max = 0x0A)
   uint8_t rx_mode; //Channel Rx Mode (do not implement)
   uint8_t tx_mode; //Channel Tx Mode (do not implement)
   uint32_t rx_freq; //Channel Rx Frequency (default radio specific)
   uint32_t tx_freq; //Channel Tx Frequency (default radio specific)
   unsigned char source[6]; //AX25 Mode Source Call Sign (default NOCALL) 
   unsigned char destination[6]; //AX25 Mode Destination Call Sign (default NOCALL)
   uint8_t tx_delay; //AX25 Mode Tx Delay (default 10ms)
   uint8_t tx_delay_end; //AX25 Mode Tx Delay End (default 100ms)
   uint8_t pid; //AX25 Mode PID (default 0x60)
   uint8_t binary_encode_method; //Binary Mode Encoding Method
   uint8_t binary_scrambling_method; //Binary Mode Scrambling Function
   uint8_t binary_flag_sync_byte; //Binary Mode Flag or Synch Bytes
   uint8_t binary_checksum_method; //Binary Mode Checksum method
   uint8_t spare;
} Radio_Configuration_t;

static const Radio_Configuration_t default_radio_config = {
   0x01,//Radio Interface mode = AX.25  
   0x0000,//Radio Time = ?????????
   0x02,//Radio Interface Baud Rate = 9600 
   0x02, //Radio TX RF Baud Rate  = 9600
   0x02, //Radio RX RF Baud Rate = 9600
   0x06, //Rx Buffer Size  = ???????????
   0x04, //Tx Buffer Size  = ???????????
   0x0A, //Tx Power Amp level  = 3W
   0x00, //Channel Rx Mode (do not implement)
   0x00, //Channel Tx Mode (do not implement)
   436000, //Channel Rx Frequency (default radio specific)
   144000, //Channel Tx Frequency (default radio specific)
   {'N','O','C','A','L','L'}, //AX25 Mode Source Call Sign  
   {'N','O','C','A','L','L'}, //AX25 Mode Destination Call Sign 
   10, //AX25 Mode Tx Delay 
   100, //AX25 Mode Tx Delay End 
   0x60, //AX25 Mode PID 
   0x00, //Binary Mode Encoding Method
   0x00, //Binary Mode Scrambling Function
   0x00, //Binary Mode Flag or Synch Bytes
   0x00, //Binary Mode Checksum method
   0x00 //Spare
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
std::string speedUpTester(bool do_increase_speed);
   //Poll last established link margin data
   //Only if SNR is above SNR_LIMIT
   //Change the transceiver transmit bitrate


/*Prepare Data for Transmission*/
   //load prepared data from C&DH into RAM
   //||LOOK INTO PACKET TRANSMISSION FOR TRANSCEIVER||
   //Configure transceiver registers (e.g. Power Level)
std::string command_transceiver(Transceiver_Command inputCommand);
std::string serialWrite(uint8_t * command); //Private

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



