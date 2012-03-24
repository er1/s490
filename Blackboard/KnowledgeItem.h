#ifndef KNOWLEDGEITEM_H
#define	KNOWLEDGEITEM_H

#include <stdint.h>
#include <vector>
#include <deque>
#include <set>
#include <sys/types.h>

#include <common/DataPoint.h>

class KnowledgeItem {
public:
    std::deque<DataPoint> dataChain;
    int updates;
    
    int ownerFd; //the owner of this KI
    std::set<int> csListeners;

    inline KnowledgeItem() {
        ownerFd = -1;
        updates = 0;
    }
	
    inline ~KnowledgeItem() {
    }
	
	void update(DataPoint);
    const DataPoint getMostRecent() const;
    std::deque<DataPoint> getRecent(size_t) const;
};

#endif	/* KNOWLEDGEITEM_H */

