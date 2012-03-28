#include <map>

#include "RunCondition.h"
#include "common/DataPoint.h"

RunCondition::RunCondition(bbtag t) {
    tag = t;
}

RunCondition::~RunCondition() {
}

bool RunCondition::canRun(const std::map<bbtag, DataPoint>& tagmap) {
    std::map<bbtag, DataPoint>::const_iterator it = tagmap.find(tag);
    
    if (it == tagmap.end() || it->second.size() < sizeof(int)) {
        return false;
    }
    
    return (it->second.unwrap<int>() != 0);
}
