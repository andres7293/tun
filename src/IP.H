#ifndef __IPV4__H__
#define __IPV4__H__

#include <bits/stdint-uintn.h>
#include <iostream>

#include "Utils.H"
#include "NetDev.H"
#include "NetBuf.H"

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

class IP_Packet {
    public:
        IP_Packet(INetBuf *netbuf): p(netbuf->getBuf()), size(netbuf->getSize()), netbuf(netbuf) {}
        IP_Packet(uint8_t *p, uint16_t size, INetBuf *netbuf): p(p), size(size), netbuf(netbuf) {}
        uint8_t* get() { return this->p; }
        uint16_t getSize() { return this->size; }
        INetBuf *getNetBuf() { return this->netbuf; }
    private:
        uint8_t *p;
        uint16_t size;
        INetBuf *netbuf;
};

class IP;
class IP_Payload: public IP_Packet {
    friend IP;
    private:
        IP_Payload(uint8_t *p, uint16_t size, INetBuf *netbuf): IP_Packet(p, size, netbuf) {}
};

class IP {
    public:
        static int ip_input(NetDev &netdev, IP_Packet &packet);
        static int ip_output(NetDev &netdev, IP_Packet &packet);
        static int validate_ip_packet_size(uint16_t ip_packet_size);
        static int validate_header(IP_Packet &packet);
        static IP_Payload getPayload(IP_Packet &packet);

        static const int MAX_IP_PACKET_SIZE = 65535;
        static const int MIN_IP_PACKET_SIZE = 20;

        static const uint8_t ICMPV4_PROTOCOL = 0x01;
};

ostream& operator << (ostream& os, IP_Header &h);

#endif
