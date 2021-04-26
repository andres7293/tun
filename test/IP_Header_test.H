#include <gtest/gtest.h>
#include "../src/IP_Header.H"

TEST(IP_Header, getVersion) {
    IP_Header_t ip_header;
    ip_header.version_headerlen = 0x45;
    ASSERT_EQ(4, IP_Header::getVersion(&ip_header));
}

TEST(IP_Header, getHeaderLen) {
    IP_Header_t ip_header;
    ip_header.version_headerlen = 0x45;
    ASSERT_EQ(5, IP_Header::getHeaderLen(&ip_header));
}

TEST(IP_Header, getHeaderLenInBytes) {
    IP_Header_t ip_header;
    ip_header.version_headerlen = 0x45;
    ASSERT_EQ(20, IP_Header::getHeaderLenInBytes(&ip_header));
}

TEST(IP_Header, getFlags) {
    IP_Header_t ip_header;
    ip_header.flags_fragoffset = 0x4000;
    ASSERT_EQ(0b010, IP_Header::getFlags(&ip_header));
}

TEST(IP_Header, getFragmentOffset) {
    IP_Header_t ip_header;
    ip_header.flags_fragoffset = 0x4000;
    ASSERT_EQ(0, IP_Header::getFragmentOffset(&ip_header));
}
