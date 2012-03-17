#ifndef CONTROLSHELL_H
#define	CONTROLSHELL_H

#include "Blackboard.h"
#include "BlackboardConnection.h"
#include "bbtags.h"
#include "bbdef.h"
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

private:
    bbtag tag;
    std::set<void (*)(bbtag, DataPoint) > callbacks;

};

#endif	/* CONTROLSHELL_H */

