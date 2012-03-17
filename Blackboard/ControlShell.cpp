/* 
 * File:   ControlShell.cpp
 * Author: chanman
 * 
 * Created on March 16, 2012, 9:45 PM
 */

#include "ControlShell.h"
#include "BlackboardConnection.h"
#include <set>
#include "bbdef.h"
#include "Packet.h"

ControlShell::ControlShell(bbtag _tag) : BlackboardConnection(BB_SOCK_PATH) {
    tag = _tag;
}

ControlShell::~ControlShell() {
}

std::deque<DataPoint> ControlShell::getRecent(int) {
    // send request
    Packet request;
    request.resize(12);
    request.setU32(0, BO_CS_GET_RECENT);
    request.setU32(4, tag);
    request.setU32(8, 1);
    sendPacket(request);

    // wait for response
    while (true) {
        waitForEvents();
        updateEvents();
    }

    return std::deque<DataPoint > (); // TODO: actually write this
}

DataPoint ControlShell::getMostRecent() {
    std::deque<DataPoint> retSet = getRecent(1);
    if (retSet.size() == 0) {
        return DataPoint();
    }
    return retSet->front();
}

void ControlShell::registerCallback(void (*callback)(bbtag, DataPoint)) {
    callbacks.insert(callback);
}

void ControlShell::releaseCallback(void (*callback)(bbtag, DataPoint)) {
    callbacks.erase(callback);
}




