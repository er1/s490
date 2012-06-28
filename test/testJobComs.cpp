/*
   Copyright 2012 Corey Clayton, Eric Chan, Mathieu Dumais-Savard

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include "../Jobs/coms.cpp"
#include <cstddef>

int main(int argc, char** argv) {

  Transceiver_Command no_op;
  no_op.command_type = COMMAND_TYPE_I;
  no_op.command = I_NO_OP;
  no_op.payload_size = 0;
  unsigned char no_op_data = NULL;
  no_op.payload_data = &no_op_data;

  Transceiver_Command transmit;
  transmit.command_type = COMMAND_TYPE_I;
  transmit.command = I_TRANSMIT;
  transmit.payload_size = 255;    //||fix size determination code - where does it live?
  unsigned char transmit_data = 4;
  transmit.payload_data = &transmit_data;

  Transceiver_Command get_config; //||get data back from commands
  get_config.command_type = COMMAND_TYPE_I;
  get_config.command = I_GET_CONFIG;
  get_config.payload_size = 0;
  unsigned char get_config_data = NULL;
  get_config.payload_data = &get_config_data;

  Transceiver_Command set_config;
  set_config.command_type = COMMAND_TYPE_I;
  set_config.command = I_SET_CONFIG;
  set_config.payload_size = 255;
  unsigned char * set_config_data = new unsigned char[42];  //||use received data from get_config
  set_config.payload_data = set_config_data;

  command_transceiver(no_op);
    sleep(1000);

  command_transceiver(transmit);
    sleep(1000);

  command_transceiver(get_config);
    sleep(1000);

  command_transceiver(set_config);
    sleep(1000);


  return 0;
}

