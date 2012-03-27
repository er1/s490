#ifndef RUNCONDITION_H
#define	RUNCONDITION_H

#include <common/common.h>

class RunCondition {
public:
    RunCondition(bbtag);
    ~RunCondition();
private:
    bbtag tag;
};

#endif	/* RUNCONDITION_H */

