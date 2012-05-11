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

#include "Uplink.h"

int main()
{
	printf("TODO: everything");

	Uplink up;
	up.prepareLink();

	Packet p;
    p.resize(4);
    p[0] = 'o';
    p[1] = 'H';
    p[2] = 'a';
    p[3] = 'i';

	up.send(p);
	up.processOutgoing();

	return 0;
}
