/*
   Copyright 2012 Space Concordia
   Author: Nick Sweet
   Subsystem Lead: Justin Jean-pierre

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

   The following lists the jobs specific to the Attitude Determination and Control System on ConSat-1.
*/


/*Subsystem Check*/
   //check related thermistors
   //check current sensors
   //check voltage sensors
   //relate battery voltage to battery capacity

/*Enable 3.3V Line*/
   //Toggle GPIO
   //||think about redundancy

/*Enable 15V Line*/
   //Toggle GPIO 
   //||think about redundancy

/*Interrupt on Line Failure*/
   //Power off warning (or brownout or overcurrent) for each 3.3v, 5v or 15v
   //Save all telemetry ASAP
   //Save all data from subsystems connected to failing line

