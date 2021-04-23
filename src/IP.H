#ifndef __IPV4__H__
#define __IPV4__H__

#include <iostream>

#include "Utils.H"

using namespace std;

struct IP_Header_t {
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

class IP_Header {
    public:
        static uint8_t getVersion(IP_Header_t *h);
        static uint8_t getHeaderLen(IP_Header_t *h);
        static uint8_t getHeaderLenInBytes(IP_Header_t *h);
        static uint8_t getFlags(IP_Header_t *h);
        static uint8_t getFragmentOffset(IP_Header_t *h);

        static const int MIN_IP_HEADER_SIZE_BYTES = 20;
};

class IP {
    public:
        static int8_t validate_ip_packet_size(uint16_t ip_packet_size);
        static int8_t validate_header(uint8_t *ip_packet, uint16_t size);
        static uint16_t validate_header_checksum(uint8_t *ip_packet, uint16_t size);
        static void convertHeaderToHostEndian(IP_Header_t *host, IP_Header_t *net);
        static void convertHeaderToNetEndian(IP_Header_t *net, IP_Header_t *host);

        static const int MAX_IP_PACKET_SIZE = 65535;
        static const int MIN_IP_PACKET_SIZE = 20;
};

ostream& operator << (ostream& os, IP_Header_t &h);

#endif
