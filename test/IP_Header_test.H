#include <gtest/gtest.h>
#include "../src/IP.H"

TEST(IP_Header, getVersion) {
    IP_Header iph;
    iph.version_headerlen = 0x45;
    ASSERT_EQ(4, iph.getVersion());
}

TEST(IP_Header, getHeaderLen) {
    IP_Header iph;
    iph.version_headerlen = 0x45;
    ASSERT_EQ(5, iph.getHeaderLen());
}

TEST(IP_Header, getHeaderLenInBytes) {
    IP_Header iph;
    iph.version_headerlen = 0x45;
    ASSERT_EQ(20, iph.getHeaderLenInBytes());
}

TEST(IP_Header, getFlags) {
    IP_Header iph;
    iph.flags_fragoffset = 0x4000;
    ASSERT_EQ(0b010, iph.getFlags());
}

TEST(IP_Header, getFragmentOffset) {
    IP_Header iph;
    iph.flags_fragoffset = 0x4000;
    ASSERT_EQ(0, iph.getFragmentOffset());
}
