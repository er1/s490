#ifndef CONTROLSHELL_H
#define	CONTROLSHELL_H

#include "BlackboardConnection.h"
#include "DataPoint.h"
#include "common.h"
#include <set>

class ControlShell : public BlackboardConnection {
public:
    ControlShell(bbtag);
    ~ControlShell();

    bool connectCS();
    void disconnectCS();
    
    std::deque<DataPoint> getRecent(int);
    DataPoint getMostRecent();

    void registerCallback(void (*)(bbtag, DataPoint));
    void releaseCallback(void (*)(bbtag, DataPoint));

	void checkForUpdates();

private:
    bbtag tag;
    std::set< void (*)(bbtag, DataPoint) > callbacks;

};

#endif	/* CONTROLSHELL_H */

