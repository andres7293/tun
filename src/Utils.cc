#include "Utils.H"

uint32_t utils::sum_every_16bits(void *addr, int count) {
    /*
        https://tools.ietf.org/html/rfc1071
     * */
    uint32_t sum = 0;
    uint16_t * ptr = (uint16_t *)addr;
    while (count > 1)  {
        /*  This is the inner loop */
        sum += * ptr++;
        count -= 2;
    }
    /*  Add left-over byte, if any */
    if (count > 0)
        sum += * (uint8_t *) ptr;
    return sum;
}

uint16_t utils::checksum(void *addr, int count, int start_sum) {
    /*
        https://tools.ietf.org/html/rfc1071
     * */
    uint32_t sum = start_sum;
    sum += sum_every_16bits(addr, count);
    /*  Fold 32-bit sum to 16 bits */
    while (sum >> 16)
        sum = (sum & 0xffff) + (sum >> 16);
    return ~sum;
}

uint16_t utils::netToHostShort(uint16_t val) {
    #if ((__BYTE_ORDER__) == (__ORDER_LITTLE_ENDIAN__))
        return utils::swap_endian_u16(val);
    #endif
        return val;
}

uint32_t utils::netToHostLong(uint32_t val) {
    #if ((__BYTE_ORDER__) == (__ORDER_LITTLE_ENDIAN__))
        return utils::swap_endian_u32(val);
    #endif
        return val;
}

uint16_t utils::hostToNetShort(uint16_t val) {
    #if ((__BYTE_ORDER__) == (__ORDER_LITTLE_ENDIAN__))
        return utils::swap_endian_u16(val);
    #endif
        return val;
}

uint32_t utils::hostToNetLong(uint32_t val) {
    #if ((__BYTE_ORDER__) == (__ORDER_LITTLE_ENDIAN__))
        return utils::swap_endian_u32(val);
    #endif
        return val;
}

uint16_t utils::swap_endian_u16(uint16_t val) {
    uint16_t result;
    uint8_t *dest = (uint8_t *) &result;
    uint8_t *src  = (uint8_t *) &val;
    dest[0] = src[1];
    dest[1] = src[0];
    return result;
}

uint32_t utils::swap_endian_u32(uint32_t val) {
    uint32_t result;
    uint8_t *dest = (uint8_t *) &result;
    uint8_t *src  = (uint8_t *) &val;
    dest[0] = src[3];
    dest[1] = src[2];
    dest[2] = src[1];
    dest[3] = src[0];
    return result;
}
