#ifndef PACKET_H
#define	PACKET_H

#include <stdint.h>
#include <vector>

class Packet : public std::vector<uint8_t> {
    public:
        Packet() : std::vector<uint8_t>() {}
        Packet(const char* start, const char* end) : std::vector<uint8_t>(start, end) {}
        Packet(const Packet& a) : std::vector<uint8_t>(a) {}
};

#endif
