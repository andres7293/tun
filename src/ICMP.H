#ifndef __ICMP_H__
#define __ICMP_H__

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
            CHECKSUM_ERROR
        };

        ICMP() {}
        virtual ~ICMP() {}
        RetCode input(Buffer ip_payload);
    private:
        RetCode validateHeaderSize(Buffer ip_payload);
        RetCode validateHeaderChecksum(Buffer ip_payload);
};

#endif
