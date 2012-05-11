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

#include "KnowledgeSource.h"
#include "BlackboardConnection.h"

KnowledgeSource::KnowledgeSource(bbtag _tag) {
    tag = _tag;
}

KnowledgeSource::~KnowledgeSource() {
}

bool KnowledgeSource::connectKS() {
    return (connectBB() && registerForKI());
}

void KnowledgeSource::disconnectKS() {
    // unregister for KI
}

bool KnowledgeSource::registerForKI() {
    log("Register for %d\n", tag);

    // send request
    Packet request;
    request.resize(8);
    request.setU32(0, BO_KS_SUBSCRIBE_AS);
    request.setU32(4, tag);
    sendPacket(request);

    log("request sent\n");

    // TODO: handle the possibility where we get a packet and and the send queue is blocked (loop over this basically)
    processOutgoing();
    //    processMsgQueue();

    Packet response;

    log("Waiting for acknowledgment from the server");
    while (true) {
        waitForEvents(); // block until we have something

        // if we have a packet to work with, deal with it
        log("Received something, is is ack?\n");
        if (recvPacket(response)) {
            if (response.getU32(0) == BO_KS_SUBSCRIPTION_SUCCESS) {
                return true;
            }
            if (response.getU32(0) == BO_KS_SUBSCRIPTION_FAILED) {
                return false;
            }
        }

        // TODO: handle any other possible packets (none yet)
    }
}

bool KnowledgeSource::update(DataPoint point) {
    Packet response;

    response.resize(8);
    response.setU32(0, BO_KS_UPDATE);
    response.setU32(4, tag);
    response.insert(response.end(), point.begin(), point.end());

    sendPacket(response);

    this->processMsgQueue();

    // actually confirm response 
    while (true) {
        waitForEvents();

        if (recvPacket(response)) {
            if (response.getU32(0) == BO_KS_UPDATE_SUCCESS) {
                return true;
            }
        }
    }

    return false;
}
