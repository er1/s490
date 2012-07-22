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
#include <unistd.h>
#include <iostream>

int main(int argc, char** argv) {
  Transceiver_Command no_op;
  no_op.command_type = COMMAND_TYPE_I;
  no_op.command = I_NO_OP;
  no_op.payload_size = 0;
  uint8_t no_op_data = NULL;
  no_op.payload_data = &no_op_data;

  Transceiver_Command transmit;
  transmit.command_type = COMMAND_TYPE_I;
  transmit.command = I_TRANSMIT;
  transmit.payload_size = 10;    //||fix size determination code - where does it live?
  uint8_t transmit_data[10] = {100,101,102,103,104,105,106,107,108,109};
  transmit.payload_data = transmit_data;

  Transceiver_Command get_config; //||get data back from commands
  get_config.command_type = COMMAND_TYPE_I;
  get_config.command = I_GET_CONFIG;
  get_config.payload_size = 0;
  uint8_t get_config_data = NULL;
  get_config.payload_data = &get_config_data;

  // Transceiver_Command set_config;
  // set_config.command_type = COMMAND_TYPE_I;
  // set_config.command = I_SET_CONFIG;
  // set_config.payload_size = 62;
  // uint8_t * set_config_data = new uint8_t[42];  //||use received data from get_config
  // set_config.payload_data = set_config_data;

    std::cout << "\n\n\n\n\n------------------NO_OP-----------------------" << std::endl;
    std::cout << command_transceiver(no_op) << std::endl;
    sleep(1);

    std::cout << "\n\n\n\n\n---------------TRANSMIT------------------------" << std::endl;
    std::cout << command_transceiver(transmit) << std::endl;
    sleep(1);

    std::cout << "\n\n\n\n\n---------------GET_CONFIG---------------------" << std::endl;
    std::cout << command_transceiver(get_config) << std::endl;
    sleep(1);

    // std::cout << "\n\n\n\n\n---------------SET_CONFIG---------------------" << std::endl;
    // std::cout << speedUpTester(true) << std::endl;
    //   sleep(1);
  
    // std::cout << "\n\n\n\n\n---------------SET_CONFIG---------------------" << std::endl;
    // std::cout << command_transceiver(set_config) << std::endl;
    //   sleep(1);

  return 0;
}

