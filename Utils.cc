#include "Utils.H"

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
