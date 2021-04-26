#ifndef __IPV4__H__
#define __IPV4__H__

#include <iostream>

#include "Utils.H"
#include "NetDev.H"
#include "IP_Header.H"

using namespace std;

class IP {
    public:
        static int ip_input(NetDev &netdev, uint8_t *p, uint16_t size);
        static int validate_ip_packet_size(uint16_t ip_packet_size);
        static int validate_header(uint8_t *ip_packet, uint16_t size);
        static uint16_t validate_header_checksum(uint8_t *ip_packet, uint16_t size);
        static uint8_t* getPayload(uint8_t *ip_packet, uint16_t size);
        static uint16_t getPayloadSize(uint8_t *ip_packet, uint16_t size);

        static const int MAX_IP_PACKET_SIZE = 65535;
        static const int MIN_IP_PACKET_SIZE = 20;

        static const uint8_t ICMPV4_PROTOCOL = 0x01;
};

ostream& operator << (ostream& os, IP_Header_t &h);

#endif
