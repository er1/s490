#include <common/common.h>

#include "Blackboard.h"
#include <common/BlackboardConnection.h>

#include <iostream>
#include <string>
#include <cstring>

using namespace std;

int main(int argc, char** argv) {
    //BlackboardConnection is needless right now
    //BlackboardConnection& blackboard = *(new BlackboardConnection);
    //blackboard.connectBB(BB_SOCK_PATH);


	/*
	  I assume that this is meant to be the test case for
	  both the KS and CS interface. The way I still see the 
	  ouside facing api to be is the following:

	  	knowledgeSource * ks = new knowledgeSource(42);
		controlShell * cs =  new controlShell();

		ks->init();
		cs->init();
		
		ks->reg();
		
		uint8_t * d =  new uint8_t[4];
		
		d[0] = 'd';
		d[1] = 'e';
		d[2] = 'r';
		d[3] = 'p';
		cs->getLast(tag, &d);
		
		deque<dataPoint> v = cs->getLast(tag, 10);


		ks->update(4, d);
		
		ks->close();

	 */


    /*
    while (true) {
        Packet p;

        p.resize(MAX_BUFFER_SIZE);

        cin.getline((char*) &(p.front()), MAX_BUFFER_SIZE);

        p.resize(strlen((char*) &(p.front())));

        blackboard.sendpacket(p);

        blackboard.performEvents();

        while (blackboard.recvpacket(p)) {
            for (size_t i = 0; i < p.size(); ++i) {
                if (p[i] <= 32 && p[i] > 127) {
                    cout << p[i];
                } else {
                    cout << '.';
                }
            }
            cout << endl;
        }
    }
    */

    //blackboard.disconnectBB();
    return 0;
}

