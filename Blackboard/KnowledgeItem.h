#ifndef KNOWLEDGEITEM_H
#define	KNOWLEDGEITEM_H

#include "stdint.h"
#include <vector>
#include <deque>
#include "sys/types.h"


typedef std::vector<uint8_t> DataPoint;

class KnowledgeItem {
private:
    std::deque<DataPoint> dataChain;
public:

    inline KnowledgeItem() {
        ownerFd = -1;
    }

    inline ~KnowledgeItem() {
    }

    void update(DataPoint);

    int ownerFd; //the owner of this KI
    std::deque<int> csListeners;

    const DataPoint getMostRecent() const;
    std::deque<DataPoint> getRecent(size_t) const;
};

#endif	/* KNOWLEDGEITEM_H */

