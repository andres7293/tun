#ifndef __ICMP_H__
#define __ICMP_H__

#include <bits/stdint-uintn.h>
#include <stdint.h>
#include "Buffer.H"

struct ICMP_Header {
    uint8_t type;
    uint8_t code;
    uint16_t checksum;
}__attribute__((packed));

class ICMP {
    public:
        enum class RetCode: int {
            OK,
            HEADER_SIZE_TOO_SHORT,
            CHECKSUM_ERROR,
            MALFORMED_ICMP_ECHO_REQUEST,
            ECHO_REPLY,
            UNKNOW
        };

        ICMP() {}
        virtual ~ICMP() {}
        RetCode input(Buffer ip_payload);
    private:
        RetCode validateHeaderSize(Buffer ip_payload);
        RetCode validateHeaderChecksum(Buffer ip_payload);
        RetCode echo_request(ICMP_Header *icmph, Buffer ip_payload);
        void echo_reply(ICMP_Header *icmp, Buffer ip_payload);

        uint16_t checksum(ICMP_Header *icmp, Buffer ip_payload);

        static const uint8_t ECHO_REQUEST_TYPE = 0x08;
        static const uint8_t ECHO_REQUEST_CODE = 0x00;

        static const uint8_t ECHO_REPLY_TYPE = 0x00;
        static const uint8_t ECHO_REPLY_CODE = 0x00;
};

#endif
