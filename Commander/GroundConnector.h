#ifndef G_CONN_H
#define G_CONN_H

#include "Connector.h"

class GroundConnector : public Connector {
public:
	GroundConnector();
	~GroundConnector();

	bool connectSat();
	void disconnectSat();

	
};

#endif
