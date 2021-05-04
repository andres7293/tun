#ifndef __ICMP_H__
#define __ICMP_H__

#include <stdint.h>
#include "IP.H"
#include "NetDev.H"

struct ICMP_Header_t {
    uint8_t type;
    uint8_t code;
    uint16_t checksum;
    uint8_t rest[4];
}__attribute__((packed));

struct ICMP_EchoRequest_t {
    uint8_t type;
    uint8_t code;
    uint16_t checksum;
    uint16_t identifier;
    uint16_t seq_number;
}__attribute__((packed));

class ICMP {
    public:
        static int icmp_input(NetDev &netdev, IP_Header *iph, uint8_t *ip_payload, uint16_t ip_payload_size);
        static int icmp_echo_request(NetDev &netdev, IP_Header *iph, uint8_t *ip_payload, uint16_t ip_payload_size);
};

ostream& operator << (ostream& os, ICMP_EchoRequest_t &h);

#endif
