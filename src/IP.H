#ifndef __IPV4__H__
#define __IPV4__H__

#include <bits/stdint-uintn.h>
#include <iostream>

#include "Utils.H"
#include "NetDev.H"
#include "NetBuf.H"
#include "Buffer.H"

using namespace std;

class IP_Header {
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

        uint8_t getVersion();
        uint8_t getHeaderLen();
        uint8_t getHeaderLenInBytes();
        uint8_t getFlags();
        uint8_t getFragmentOffset();

        static const int MIN_IP_HEADER_SIZE_BYTES = 20;
}__attribute__((packed));

class IP {
    public:

        enum class RetCode: int {
            OK,
            PACKET_SIZE_GREATER_THAN_NETBUF_SIZE,
            PACKET_SIZE_LESS_THAN_MIN_PACKET_SIZE,
            PACKET_SIZE_GREATER_THAN_MAX_PACKET_SIZE,
            INVALID_IP_VERSION,
            HEADER_LEN_DIFFERENT_FROM_20_BYTES,
            EXPECTED_PACKET_SIZE_DOESNT_MATCH_WITH_RECEIVED_PACKET_SIZE,
            INVALID_HEADER_CHECKSUM
        };

        IP(NetDev& netdev): netdev(netdev) {}
        RetCode input(INetBuf& nbuf, Buffer packet);
        RetCode validateInputSize(INetBuf& nbuf, uint16_t packetSize);
        RetCode validateHeader(Buffer packet);
        RetCode validateHeaderChecksum(Buffer packet);

        static const int MAX_IP_PACKET_SIZE = 65535;
        static const int MIN_IP_PACKET_SIZE = 20;

        static const uint8_t IPV4_VERSION = 0x04;
        static const uint8_t ICMPV4_PROTOCOL = 0x01;
    private:
        NetDev& netdev;
};

ostream& operator << (ostream& os, IP_Header &h);
ostream& operator << (ostream& os, IP::RetCode &ret);

#endif
