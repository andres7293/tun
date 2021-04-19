#ifndef __IPV4__H__
#define __IPV4__H__

#include <cstdint>
#include <iostream>
using namespace std;

struct IPv4_Header_t {
    public:
        uint8_t version_headerlen; //4 bits for version and 4 bits for header length;
        uint8_t tos;
        uint16_t total_len; //total length of datagram
        uint16_t id;
        uint16_t flags_fragoffset; //3 bits for flags 13bits for fragment offset
        uint8_t ttl;
        uint8_t protocol;
        uint16_t header_checksum;
        uint32_t src_addr;
        uint32_t dst_addr;
        
        static const int VERSION = 4;
}__attribute__((packed));

class IPv4 {
    public:
        IPv4(const uint8_t *net_frame);
    private:
        IPv4_Header_t ip_header;
        uint8_t *payload;
        unsigned int payload_size;
};

uint16_t netToHostShort(uint16_t val);
uint32_t netToHostLong(uint32_t val);

ostream& operator << (ostream& os, IPv4_Header_t &h);

#endif
