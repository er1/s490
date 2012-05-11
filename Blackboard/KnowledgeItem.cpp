/*
   Copyright 2012 Corey Clayton, Eric Chan, Mathieu Dumais-Savard

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

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
