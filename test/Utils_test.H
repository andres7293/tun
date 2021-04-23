#include <gtest/gtest.h>
#include "../src/Utils.H"

TEST(utils, netToHostShort) {
    uint16_t big_endian = 0xAABB;
    uint16_t little_endian = 0xBBAA;
    #if ((__BYTE_ORDER__) == (__ORDER_LITTLE_ENDIAN__))
        ASSERT_EQ(little_endian, utils::netToHostShort(big_endian));
        return;
    #endif
        ASSERT_EQ(big_endian, utils::netToHostShort(big_endian));
}

TEST(utils, netToHostLong) {
    uint32_t big_endian = 0xAABBCCDD;
    uint32_t little_endian = 0xDDCCBBAA;
    #if ((__BYTE_ORDER__) == (__ORDER_LITTLE_ENDIAN__))
        ASSERT_EQ(little_endian, utils::netToHostLong(big_endian));
        return;
    #endif
        ASSERT_EQ(big_endian, utils::netToHostLong(big_endian));
}

TEST(utils, hostToNetShort) {
    uint16_t big_endian = 0xAABB;
    uint16_t little_endian = 0xBBAA;
    #if ((__BYTE_ORDER__) == (__ORDER_LITTLE_ENDIAN__))
        ASSERT_EQ(little_endian, utils::hostToNetShort(big_endian));
        return;
    #endif
        ASSERT_EQ(big_endian, utils::hostToNetShort(big_endian));
}

TEST(utils, hostToNetLong) {
    uint32_t big_endian = 0xAABBCCDD;
    uint32_t little_endian = 0xDDCCBBAA;
    #if ((__BYTE_ORDER__) == (__ORDER_LITTLE_ENDIAN__))
        ASSERT_EQ(little_endian, utils::hostToNetLong(big_endian));
        return;
    #endif
        ASSERT_EQ(big_endian, utils::hostToNetLong(big_endian));
}

TEST(utils, swap_endian_u16) {
    uint16_t big_endian = 0xAABB;
    uint16_t little_endian = 0xBBAA;
    ASSERT_EQ(little_endian, utils::swap_endian_u16(big_endian));
    ASSERT_EQ(big_endian, utils::swap_endian_u16(little_endian));
}

TEST(utils, swap_endian_u32) {
    uint32_t big_endian = 0xAABBCCDD;
    uint32_t little_endian = 0xDDCCBBAA;
    ASSERT_EQ(little_endian, utils::swap_endian_u32(big_endian));
    ASSERT_EQ(big_endian, utils::swap_endian_u32(little_endian));
}
