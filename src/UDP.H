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
        enum class RetCode: int {
            OK,
            PACKET_SIZE_LESS_THAN_MIN_PACKET_SIZE,
            EXPECTED_PACKET_SIZE_DOESNT_MATCH_WITH_RECEIVED_PACKET_SIZE,
            INVALID_CHECKSUM
        };

        RetCode input(Buffer ip_payload);
    private:
        RetCode validatePacketSize(Buffer ip_payload);
        RetCode validateChecksum(Buffer ip_payload);

        static const int MIN_PACKET_SIZE = sizeof(UDP_Header);
};

#endif
