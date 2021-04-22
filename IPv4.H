#ifndef __IPV4__H__
#define __IPV4__H__

#include <iostream>

#include "Utils.H"

using namespace std;

struct IPv4_Header_t {
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

class IPv4_Header {
    public:
        static uint8_t getVersion(IPv4_Header_t *h);
        static uint8_t getHeaderLen(IPv4_Header_t *h);
        static uint8_t getHeaderLenInBytes(IPv4_Header_t *h);
        static uint8_t getFlags(IPv4_Header_t *h);
        static uint8_t getFragmentOffset(IPv4_Header_t *h);
        static uint16_t  validate_header_checksum(uint8_t *header_frame, uint8_t header_size);
        static void    convertHeaderToHostEndian(IPv4_Header_t *host, IPv4_Header_t *net);
        static void    convertHeaderToNetEndian(IPv4_Header_t *net, IPv4_Header_t *host);

        static const int MIN_IP_HEADER_SIZE_BYTES = 20;
};

ostream& operator << (ostream& os, IPv4_Header_t &h);

#endif
