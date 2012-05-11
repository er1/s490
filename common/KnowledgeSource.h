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

#ifndef KNOWLEDGESOURCE_H
#define	KNOWLEDGESOURCE_H

#include "BlackboardConnection.h"
#include "DataPoint.h"

class KnowledgeSource : public BlackboardConnection {
public:
    KnowledgeSource(bbtag);
    ~KnowledgeSource();

    bool connectKS();
    void disconnectKS();

    bool update(DataPoint);

private:
    bool registerForKI();
    bbtag tag;
};

#endif	/* KNOWLEDGESOURCE_H */

