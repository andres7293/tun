#ifndef __UDPV4_H__
#define __UDPV4_H__

#include "Buffer.H"
#include "Utils.H"

struct UDP_Header {
    uint16_t src_port;
    uint16_t dst_port;
    uint16_t length;
    uint16_t checksum;
};

class UDP {
    public:
        enum class RetCode {
        };

        RetCode input(Buffer ip_payload);
    private:
};

#endif
