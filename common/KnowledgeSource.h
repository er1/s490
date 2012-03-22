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

