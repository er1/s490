#ifndef CONTROLSHELL_H
#define	CONTROLSHELL_H

#inclued "BlackboardConnection.h"
#include "bbtags.h"
#include "bbdef.h"

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
    std::deque<void (*)(bbtag, DataPoint) > callbacks;

};

#endif	/* CONTROLSHELL_H */

