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
	unsigned int maxDataPts; 
    unsigned int updates;

    int ownerFd; //the owner of this KI
    std::set<int> csListeners;

    inline KnowledgeItem() {
        ownerFd = -1;
        updates = 0;
		maxDataPts = 50;
    }

    inline ~KnowledgeItem() {
    }

    void update(DataPoint);
	void setMaxDataPts(unsigned int);
    const DataPoint getMostRecent() const;
    std::deque<DataPoint> getRecent(size_t) const;
};

#endif	/* KNOWLEDGEITEM_H */

