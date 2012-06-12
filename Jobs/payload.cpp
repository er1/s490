/*
   Copyright 2012 Space Concordia
   Author: Nick Sweet
   Subsystem Lead: Michelle Boyce

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

   The following lists the jobs specific to the Payload System on ConSat-1.
*/

const unsigned double LP_SAMPLE_RATE = 2/3; //in seconds
const unsigned double GT_EVENT_SAMPLE_RATE = 1/20000; //in seconds
const unsigned double GT_SPECTRUM_SAMPLE_RATE = 2/3; //in seconds
const unsigned double GA_SAMPLE_RATE = 2/3; //in seconds
const unsigned int GT_SPECTRUM_SIZE = 100; //resolution of GT spectrum

/*Subsystem Check*/
   //related thermistor readings
   //check LP calibration
   //check GT calibration
   //check GA calibration

/*Langmuir Probe*/
   //activate langmuir probe
   //read samples at LP_SAMPLE_RATE
   //(toggle) mark raw data slice for transmission


/*Geiger Tube Events*/
   //activate geiger tube
   //read samples at GT_EVENT_SAMPLE_RATE
   //call Geiger Tube Spectra


/*Geiger Tube Spectra*/
   //timestamp current geiger tube samples in memory
   //save geiger tube samples to SSD and mark for transmission
   //(toggle) mark raw data slice for transmission
   //clear geiger tube memory space
   //call Geiger Tube Events 


/*Langmuir Probe*/
   //activate langmuir probe
   //read samples at LP_SAMPLE_RATE
   //(toggle) mark raw data slice for transmission
