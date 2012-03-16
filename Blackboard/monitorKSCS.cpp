#include "common.h"
#include "bbdef.h"
#include "bbtags.h"

#include "Blackboard.h"
#include "BlackboardConnection.h"

#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv) {
    BlackboardConnection& blackboard = *(new BlackboardConnection);
    blackboard.connectBB(BB_SOCK_PATH);

    while (true) {
        Packet p;
        
        p.resize(MAX_BUFFER_SIZE);
        
        cin.getline((char*)&(p.front()), MAX_BUFFER_SIZE);
        
        p.resize(strnlen((char*)&(p.front()), MAX_BUFFER_SIZE));
        
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
    
    
    blackboard.disconnectBB();
    return 0;
}

