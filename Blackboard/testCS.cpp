#include "ControlShell.h"
#include "KnowledgeSource.h"
#include "BlackboardConnection.h"
#include "unistd.h"
#include "assert.h"
int main(int argc, char** argv) 
{

	/*
	  in order to test the CS, we need to 
	  have the BB in a known state.

	  To do this we will first make a KS 
	  and make some data.
	*/

	int tag = 490;

	KnowledgeSource myKS(tag);

    if (myKS.connectKS()) 
	{
        log("connected\n");
    }
	else 
	{
        log("Could not connect, BB did not allow me to register for tag %d\n", tag);
        return 1;
    }

    DataPoint p;
    p.resize(6);


	p[0] = 'M';
	p[1] = 'c';
	p[2] = 'G';
	p[3] = 'e';
	p[4] = 'r';
	p[5] = 'p';
	

	if (myKS.update(p)) 
	{
		log("updated with ack\n");
	}
	else
	{
		log("update failed\n");
	}

    myKS.disconnectKS();

/////////////////////////////////////////////////	

    ControlShell myCS(tag);
   
    myCS.connectCS();
    
	std::deque<DataPoint> dq1 =  myCS.getRecent(5);
	std::deque<DataPoint> dq2 =  myCS.getRecent(5);
    DataPoint dp = myCS.getMostRecent();
    myCS.disconnectCS();

	assert(dq1.size() == 1);
	for(uint32_t i=0; i<dq1[0].size(); ++i) {
		assert(p[i] == dq1[0][i]);
	}
	assert(dq2.size() == 1);
	for(uint32_t i=0; i<dq1[0].size(); ++i) {
		assert(p[i] == dq2[0][i]);
	}
	assert(dp.size() == p.size());
	for(uint32_t i=0; i<p.size(); ++i) {
		assert(p[i] == dp[i]);
	}

    return 0;
}

