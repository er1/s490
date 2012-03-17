#include "ControlShell.h"

int main(int argc, char** argv) {
    ControlShell myCS(42);
   
    myCS.connectCS();
    
    myCS.getRecent(5);
    
    myCS.disconnectCS();
    
    return 0;
}

