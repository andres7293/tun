#ifndef __UTILS__H__
#define __UTILS__H__

#include <stdint.h>

namespace utils {
    uint16_t netToHostShort(uint16_t val);
    uint32_t netToHostLong(uint32_t val);

    uint16_t swap_endian_u16(uint16_t val);
    uint32_t swap_endian_u32(uint32_t val);
};

#endif
