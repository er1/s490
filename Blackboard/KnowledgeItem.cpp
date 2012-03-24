#include "KnowledgeItem.h"

// update the KI with a new DataPoint
void KnowledgeItem::update(DataPoint point) {
    // add the data point to the front of data chain
    dataChain.push_front(point);

    // clean out unneeded data points
    while (dataChain.size() > 50) // amortized O(1)
        dataChain.pop_back();

    ++updates;
}

// return the first most recent data point
const DataPoint KnowledgeItem::getMostRecent() const {
    DataPoint ret;
    ret = dataChain.front();
    return ret;
}

// return the n most recent data points
std::deque<DataPoint> KnowledgeItem::getRecent(size_t numPoints) const {
    if (numPoints > dataChain.size()) {
        numPoints = dataChain.size();
    }

    std::deque<DataPoint> ret(dataChain.begin(), dataChain.begin() + numPoints);
    return ret;
}
