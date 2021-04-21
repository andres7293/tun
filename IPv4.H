#ifndef __IPV4__H__
#define __IPV4__H__

#include <bits/stdint-uintn.h>
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
}__attribute__((packed));

enum class IPv4_Protocol {
    ICMP = 0x01,
    UNKNOW = 0xff
};

class IP_Header {
    public:
        void parse(uint8_t *net_frame);
        uint8_t getVersion();
        uint8_t getHeaderLen();
        uint8_t getFlags();
        uint8_t getFragmentOffset();
        IPv4_Protocol getProtocol();

        IPv4_Header_t header;
};

uint16_t netToHostShort(uint16_t val);
uint32_t netToHostLong(uint32_t val);

ostream& operator << (ostream& os, IPv4_Header_t &h);

#endif
