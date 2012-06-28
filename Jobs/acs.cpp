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
   //Check magnetometer


/*Take Magnetometer Readings*/
   //Request magnetometer activation
   //Check registration with magnetometer KS
   //Check magnetometer activation
   //Listen for KS updates
   //Take KS updates
   //Request magnetometer deactivation


/*Filter Magnetometer Reading*/


/*Import Position Data From ODS*/


/*Calculate Attitude*/
   //Take IGRF values at given position
   //Compare IGRF values to magnetometer reading
   //Vector difference = attitude

/*Verify Attitude Calculation*/


/*Update Blackboard with Attitude Data*/

