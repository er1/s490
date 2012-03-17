#include "KnowledgeSource.h"
#include "BlackboardConnection.h"

int main(int argc, char** argv) {
    KnowledgeSource myKS(42);
    
    myKS.connectKS();
    
    log("connected maybe\n");
    
    DataPoint p;
    p.resize(4);
    
    p[0] = 'd';
    p[1] = 'e';
    p[2] = 'r';
    p[3] = 'p';
        
    myKS.update(p);
    
    log("updated maybe\n");
    
    myKS.updateEvents();
    
    myKS.disconnectKS();
    
    return 0;
}

