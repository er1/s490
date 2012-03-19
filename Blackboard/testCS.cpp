#include "ControlShell.h"
#include "KnowledgeSource.h"
#include "BlackboardConnection.h"
#include "unistd.h"
#include "assert.h"
#include "stdio.h"
#include "minunit.h"

int tests_run = 0;

int tag = 490;

DataPoint p;

KnowledgeSource myKS(tag);

ControlShell myCS(tag);

static char * test_connect(){
    bool con = myCS.connectCS();
	mu_assert("connectCS returned false!", con == true);
	return 0;
}

static char * test_getRecent(){
	std::deque<DataPoint> dq1 =  myCS.getRecent(5);
	std::deque<DataPoint> dq2 =  myCS.getRecent(5);

	mu_assert("Got a number of data points != 1", dq1.size() == 1);
	for(uint32_t i=0; i<dq1[0].size(); ++i) {
		mu_assert("getRecent()1: Corrupt Data", p[i] == dq1[0][i]);
	}
	assert(dq2.size() == 1);
	for(uint32_t i=0; i<dq1[0].size(); ++i) {
		mu_assert("getRecent()2: Corrupt Data", p[i] == dq2[0][i]);
	}
	return 0;
}

static char * test_getMostRecent(){
	DataPoint dp = myCS.getMostRecent();

	assert(dp.size() == p.size());
	for(uint32_t i=0; i<p.size(); ++i) {
		mu_assert("getMostRecent(): Corrupt Data", p[i] == dp[i]);
	}
	return 0;
}

static char * all_tests(){
	mu_run_test(test_connect);
	mu_run_test(test_getRecent);
	mu_run_test(test_getMostRecent);
	return 0;
}

int main(int argc, char** argv) 
{

	/*
	  in order to test the CS, we need to 
	  have the BB in a known state.

	  To do this we will first make a KS 
	  and make some data.
	*/

    if (myKS.connectKS()) 
	{
        log("connected\n");
    }
	else 
	{
        log("Could not connect, BB did not allow me to register for tag %d\n", tag);
        return 1;
    }

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
// setup complete
/////////////////////////////////////////////////	
   
	char *result = all_tests();
	if (result != 0) {
		printf("%s\n", result);
	}
	else {
		printf("ALL TESTS PASSED\n");
	}
	printf("Tests run: %d\n", tests_run);
    
    myCS.disconnectCS();

    return 0;
}

