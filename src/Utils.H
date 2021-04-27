#ifndef __UTILS__H__
#define __UTILS__H__

#include <stdint.h>

namespace utils {
    uint32_t sum_every_16bits(void *addr, uint16_t count);
    uint16_t checksum(void *addr, uint16_t count, uint32_t start_sum);

    uint16_t netToHostShort(uint16_t val);
    uint32_t netToHostLong(uint32_t val);

    uint16_t hostToNetShort(uint16_t val);
    uint32_t hostToNetLong(uint32_t val);

    uint16_t swap_endian_u16(uint16_t val);
    uint32_t swap_endian_u32(uint32_t val);
};

#endif
