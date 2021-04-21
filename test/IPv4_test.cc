#include <gtest/gtest.h>
#include "../IPv4.H"
#include "../Utils.H"

/*network ip packet*/
const uint8_t net_ip_frame_raw[] = {0x45, 0x00, 0x00, 0x54, 0xf2, 0xc8, 0x40, 0x00, 0x40, 0x01, 0x49, 0xde, 0x7f, 0x00, 0x00, 0x01, 0x7f, 0x00, 0x00, 0x01, 0x08, 0x00, 0x4f, 0xff, 0x61, 0xfa, 0x00, 0x01, 0x8f, 0xe1, 0x7f, 0x60, 0x00, 0x00, 0x00, 0x00, 0x76, 0xf0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37};

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

TEST(IPv4_Header, validate_checksum) {
    ASSERT_EQ(true, IPv4_Header::validate_checksum((uint8_t *)net_ip_frame_raw));
    uint8_t *zeroBuf = new uint8_t[20];
    ASSERT_EQ(false, IPv4_Header::validate_checksum(zeroBuf));
    delete[] zeroBuf;
}

TEST(utils, netToHostShort) {
    uint16_t big_endian = 0xAABB;
    uint16_t little_endian = 0xBBAA;
    ASSERT_EQ(little_endian, utils::netToHostShort(big_endian));
}

TEST(utils, netToHostLong) {
    uint32_t big_endian = 0xAABBCCDD;
    uint32_t little_endian = 0xDDCCBBAA;
    ASSERT_EQ(little_endian, utils::netToHostLong(big_endian));
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
