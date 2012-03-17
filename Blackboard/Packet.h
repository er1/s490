#ifndef PACKET_H
#define	PACKET_H

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
        return ntohs(*(short*)&at(index));
    }
    inline const uint32_t getU32(const int index) const {
        return ntohs(*(long*)&at(index));
    }
  
    inline void setU8(const int index, const uint8_t val) {
        at(index) = val;
    }
    inline void setU16(const int index, const uint16_t val) {
        *(short*)&at(index) = htons(val);
    }
    inline void setU32(const int index, const uint32_t val) {
        *(long*)&at(index) = htonl(val);
    }
    
};

#endif
