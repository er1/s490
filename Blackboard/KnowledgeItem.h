#ifndef KNOWLEDGEITEM_H
#define	KNOWLEDGEITEM_H

#include "stdint.h"
#include <vector>
#include <deque>
#include <set>
#include "sys/types.h"

#include "DataPoint.h"

class KnowledgeItem {
private:
    std::deque<DataPoint> dataChain;
public:
	
    int ownerFd; //the owner of this KI
    std::set<int> csListeners;

    inline KnowledgeItem() {
        ownerFd = -1;
    }
	
    inline ~KnowledgeItem() {
    }
	
	void update(DataPoint);
    const DataPoint getMostRecent() const;
    std::deque<DataPoint> getRecent(size_t) const;
};

#endif	/* KNOWLEDGEITEM_H */

