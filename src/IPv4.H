#ifndef __IPV4_H__
#define __IPV4_H__

#include <bits/stdint-uintn.h>
#include <string>

#include "Utils.H"
#include "NetDev.H"
#include "NetBuf.H"
#include "Buffer.H"
#include "Protocol.H"
#include "ICMPv4.H"

class IPv4Header;
class Stack;

class IPv4: public Protocol
{
    public:
        IPv4(): stack(nullptr) {}
        virtual ~IPv4() {}

        void init(Stack& stack) override;
        int input(Packet& packet) override;
        int output(Packet& packet) override;
        unsigned int getProtocolSize(unsigned int size) override;
    private:
        int checksum(IPv4Header* header);

        static const uint8_t ICMPV4_PROTOCOL = 0x01;
        static const uint8_t UDPV4_PROTOCOL = 0x11;

        Stack* stack;
        ICMPv4 icmp4 {};
};

class IPv4Header
{
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

        static const int MAX_PACKET_SIZE = 65535;
        static const int MIN_PACKET_SIZE = 20;

        static const int MIN_HEADER_SIZE_BYTES = 20;
        static const uint8_t IPV4_VERSION = 0x04;
}__attribute__((packed));

class IPv4Addr {
    public:
        IPv4Addr();
        IPv4Addr(uint32_t addr);
        IPv4Addr(std::string addr);
        std::string toString();
        uint32_t getAddress();
    private:
        uint8_t addr[4];
};

#endif
