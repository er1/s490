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

#include <common/common.h>
#include <common/ControlShell.h>

#include <iostream>
#include <string>
#include <cstring>

using namespace std;

void update(bbtag tag, const DataPoint& dp) {
    cout << tag << "\t[ ";

    for (DataPoint::const_iterator it = dp.begin(); it != dp.end(); ++it) {
        cout << (int)(*it) << ' ';
    }
    
    cout << ']' << endl;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: monitorCS <tag>" << endl;
        exit(-1);
    }

    bbtag tag;
    sscanf(argv[1], "%d", &tag);

    ControlShell myCS(tag);
    if (!myCS.connectCS()) {
        cerr << "no bb" << endl;
        exit(-1);
    }

	cout << "Monitoring tag " << tag << endl << "The last 10 data points are:" << endl;

	std::deque<DataPoint> dq = myCS.getRecent(10);
	std::deque<DataPoint>::const_iterator dit;
	for(dit = dq.begin(); dit != dq.end(); ++dit){
		cout << "DataPoint [ " << endl;
		
		for(DataPoint::const_iterator it = (*dit).begin(); it!= (*dit).end(); ++it){
			cout  << (int)(*it) << " ";
		}

		cout << "]" << endl;
	}

    myCS.registerCallback(update);

    while (true) {
        myCS.waitForEvents();
        myCS.processMsgQueue();
        myCS.checkForUpdates();
    }

    myCS.disconnectCS();

    return 0;
}

