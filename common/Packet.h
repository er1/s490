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

#ifndef PACKET_H
#define	PACKET_H

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdint.h>
#include <vector>

class Packet : public std::vector<uint8_t> {
public:

    inline Packet() : std::vector<uint8_t>() {
    }

    inline Packet(const char* start, const char* end) : std::vector<uint8_t>(start, end) {
    }

    inline Packet(const Packet& a) : std::vector<uint8_t>(a) {
    }

    inline const uint8_t getU8(const int index) const {
        return at(index);
    }

    inline const uint16_t getU16(const int index) const {
        return ntohs(*(short*) &at(index));
    }

    inline const uint32_t getU32(const int index) const {
        return ntohl(*(long*) &at(index));
    }

    inline void setU8(const int index, const uint8_t val) {
        at(index) = val;
    }

    inline void setU16(const int index, const uint16_t val) {
        uint8_t* ptr = &front();
        *(short*) (ptr + index) = htons(val);
    }

    inline void setU32(const int index, const uint32_t val) {
        uint8_t* ptr = &front();
        *(long*) (ptr + index) = htonl(val);
    }

};

#endif
