#include <bits/stdint-uintn.h>
#include <gtest/gtest.h>
#include "../IPv4.H"
#include "../Utils.H"

/*network ip packet*/
const uint8_t net_ip_frame_raw[] = {0x45, 0x00, 0x00, 0x54, 0xf2, 0xc8, 0x40, 0x00, 0x40, 0x01, 0x49, 0xde, 0x7f, 0x00, 0x00, 0x01, 0x7f, 0x00, 0x00, 0x01, 0x08, 0x00, 0x4f, 0xff, 0x61, 0xfa, 0x00, 0x01, 0x8f, 0xe1, 0x7f, 0x60, 0x00, 0x00, 0x00, 0x00, 0x76, 0xf0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37};

TEST(IPv4_Header, validate_header) {
    uint8_t *badHeader = new uint8_t[20];
    ASSERT_EQ(-1, IPv4_Header::validate_header(badHeader, 0));
    ASSERT_EQ(-2, IPv4_Header::validate_header(badHeader, 20));
    //test bad checksum
    badHeader[0] = 0x45;
    ASSERT_EQ(-3, IPv4_Header::validate_header(badHeader, 20));
    //good case
    ASSERT_EQ(0, IPv4_Header::validate_header((uint8_t *)net_ip_frame_raw, sizeof(net_ip_frame_raw)));
    delete[] badHeader;
}

TEST(IPv4_Header, getVersion) {
    IPv4_Header_t ip_header;
    ip_header.version_headerlen = 0x45;
    ASSERT_EQ(4, IPv4_Header::getVersion(&ip_header));
}

TEST(IPv4_Header, getHeaderLen) {
    IPv4_Header_t ip_header;
    ip_header.version_headerlen = 0x45;
    ASSERT_EQ(5, IPv4_Header::getHeaderLen(&ip_header));
}

TEST(IPv4_Header, getHeaderLenInBytes) {
    IPv4_Header_t ip_header;
    ip_header.version_headerlen = 0x45;
    ASSERT_EQ(20, IPv4_Header::getHeaderLenInBytes(&ip_header));
}

TEST(IPv4_Header, getFlags) {
    IPv4_Header_t ip_header;
    ip_header.flags_fragoffset = 0x4000;
    ASSERT_EQ(0b010, IPv4_Header::getFlags(&ip_header));
}

TEST(IPv4_Header, getFragmentOffset) {
    IPv4_Header_t ip_header;
    ip_header.flags_fragoffset = 0x4000;
    ASSERT_EQ(0, IPv4_Header::getFragmentOffset(&ip_header));
}

TEST(IPv4_Header, validate_header_checksum) {
    ASSERT_EQ(0, IPv4_Header::validate_header_checksum((uint8_t *)net_ip_frame_raw, 20));
    uint8_t *zeroBuf = new uint8_t[20];
    ASSERT_NE(1, IPv4_Header::validate_header_checksum(zeroBuf, 20));
    delete[] zeroBuf;
}

TEST(IPv4_Header, convertHeaderToHostEndian) {
    IPv4_Header_t neth = {
        .version_headerlen = 0x45,
        .tos               = 0x00,
        .total_len         = 0xAABB,
        .id                = 0xAABB,
        .flags_fragoffset  = 0x0040,
        .ttl               = 0xAA,
        .protocol          = 0x01,
        .header_checksum   = 0xAABB,
        .src_addr          = 0xAABBCCDD,
        .dst_addr          = 0xAABBCCDD
    };
    IPv4_Header_t hosth;
    IPv4_Header::convertHeaderToHostEndian(&hosth, &neth);
    ASSERT_EQ(0x4, IPv4_Header::getVersion(&hosth));
    ASSERT_EQ(0x5, IPv4_Header::getHeaderLen(&hosth));
    ASSERT_EQ(20, IPv4_Header::getHeaderLenInBytes(&hosth));
    ASSERT_EQ(0xBBAA, hosth.total_len);
    ASSERT_EQ(0xBBAA, hosth.id);
    ASSERT_EQ(0b010, IPv4_Header::getFlags(&hosth));
    ASSERT_EQ(0, IPv4_Header::getFragmentOffset(&hosth));
    ASSERT_EQ(0xAA, hosth.ttl);
    ASSERT_EQ(0x1, hosth.protocol);
    ASSERT_EQ(0xBBAA, hosth.header_checksum);
    ASSERT_EQ(0xDDCCBBAA, hosth.src_addr);
    ASSERT_EQ(0xDDCCBBAA, hosth.dst_addr);
}

TEST(IPv4_Header, convertHeaderToNetEndian) {
    IPv4_Header_t hosth = {
        .version_headerlen = 0x45,
        .tos               = 0x00,
        .total_len         = 0xAABB,
        .id                = 0xAABB,
        .flags_fragoffset  = 0x0040,
        .ttl               = 0xAA,
        .protocol          = 0x01,
        .header_checksum   = 0xAABB,
        .src_addr          = 0xAABBCCDD,
        .dst_addr          = 0xAABBCCDD
    };
    IPv4_Header_t neth;
    IPv4_Header::convertHeaderToNetEndian(&neth, &hosth);
    ASSERT_EQ(0x4, IPv4_Header::getVersion(&neth));
    ASSERT_EQ(0x5, IPv4_Header::getHeaderLen(&neth));
    ASSERT_EQ(20, IPv4_Header::getHeaderLenInBytes(&neth));
    ASSERT_EQ(0xBBAA, neth.total_len);
    ASSERT_EQ(0xBBAA, neth.id);
    ASSERT_EQ(0b010, IPv4_Header::getFlags(&neth));
    ASSERT_EQ(0, IPv4_Header::getFragmentOffset(&neth));
    ASSERT_EQ(0xAA, neth.ttl);
    ASSERT_EQ(0x1, neth.protocol);
    ASSERT_EQ(0xBBAA, neth.header_checksum);
    ASSERT_EQ(0xDDCCBBAA, neth.src_addr);
    ASSERT_EQ(0xDDCCBBAA, neth.dst_addr);
}

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

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
