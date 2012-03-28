#ifndef RUNCONDITION_H
#define	RUNCONDITION_H

#include <common/common.h>
#include <common/DataPoint.h>

class RunCondition {
public:
    RunCondition(bbtag);
    ~RunCondition();
    
    bool canRun(const std::map<bbtag, DataPoint>&);
//private:
    bbtag tag;
};

#endif	/* RUNCONDITION_H */

