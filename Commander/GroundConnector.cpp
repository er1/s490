#include "GroundConnector.h"
#include "../common/satdef.h"

GroundConnector::GroundConnector(){
}

GroundConnector::~GroundConnector(){
}

bool GroundConnector::connectSat(){
#ifdef USE_AX25
	return connect(NULL, NULL);
#else
	return connect(TEST_SAT_IP, TEST_PORT);
#endif
}

void GroundConnector::disconnectSat(){
	disconnect();
}
