#include "KnowledgeItem.h"

void KnowledgeItem::update(DataPoint point) {
    dataChain.push_front(point);
}

const DataPoint KnowledgeItem::getMostRecent() const {
    DataPoint ret;
    ret = dataChain.front();
    return ret;
}

std::deque<DataPoint> KnowledgeItem::getRecent(size_t numPoints) const {
    if (numPoints > dataChain.size()) {
        numPoints = dataChain.size();
    }

    std::deque<DataPoint> ret(dataChain.begin(), dataChain.begin() + numPoints);
    return ret;
}
