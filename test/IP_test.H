#include <gtest/gtest.h>
#include "../src/IP.H"
#include "../src/NetDev.H"
#include "../src/TunIf.H"

/*network ip packet*/
const uint8_t net_ip_frame_raw[] = {0x45, 0x00, 0x00, 0x54, 0xf2, 0xc8, 0x40, 0x00, 0x40, 0x01, 0x49, 0xde, 0x7f, 0x00, 0x00, 0x01, 0x7f, 0x00, 0x00, 0x01, 0x08, 0x00, 0x4f, 0xff, 0x61, 0xfa, 0x00, 0x01, 0x8f, 0xe1, 0x7f, 0x60, 0x00, 0x00, 0x00, 0x00, 0x76, 0xf0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37};

TunIf tun("dummytun");
NetDev netdev(tun);

TEST(IP, ip_input) {
    //TODO test ipv6 version
    IP_Packet badHeader(new uint8_t[20], 20);
    IP_Packet zeroSizePacket(nullptr, 0);
    IP_Packet goodPacket((uint8_t *)net_ip_frame_raw, sizeof(net_ip_frame_raw));

    memset((uint8_t *) badHeader.get(), 0, 20);
    ASSERT_EQ(-1, IP::ip_input(netdev, zeroSizePacket));
    ASSERT_EQ(-2, IP::ip_input(netdev, badHeader));
    ASSERT_EQ(0, IP::ip_input(netdev, goodPacket));
    delete[] badHeader.get();
}

TEST(IP, validate_ip_packet_size) {
    ASSERT_EQ(-1, IP::validate_ip_packet_size(0));
    ASSERT_EQ(-1, IP::validate_ip_packet_size(19));
    ASSERT_EQ(0, IP::validate_ip_packet_size(65535));
    ASSERT_EQ(0, IP::validate_ip_packet_size(1024));
    ASSERT_EQ(0, IP::validate_ip_packet_size(20));
}

TEST(IP, validate_header) {
    uint8_t *zero = new uint8_t[21];
    memset((uint8_t *) zero, 0, 21);

    IP_Packet badHeader(zero, 21);
    IP_Packet zeroSizePacket(nullptr, 0);
    IP_Packet goodPacket((uint8_t *)net_ip_frame_raw, sizeof(net_ip_frame_raw));
    IP_Packet tooLargePacket((uint8_t *)net_ip_frame_raw, 1024);

    ASSERT_EQ(-1, IP::validate_header(zeroSizePacket));
    ASSERT_EQ(-2, IP::validate_header(badHeader));
    //test bad checksum
    badHeader.get()[0] = 0x45;
    ASSERT_EQ(-3, IP::validate_header(badHeader));
    //test if total_len of header doesnt match with the current packet size
    ASSERT_EQ(-4, IP::validate_header(tooLargePacket));
    //good case
    ASSERT_EQ(0, IP::validate_header(goodPacket));
    delete[] zero;
}

TEST(IP, getPayload) {
    IP_Packet packet((uint8_t *) net_ip_frame_raw, sizeof(net_ip_frame_raw));
    IP_Payload payload = IP::getPayload(packet);
    ASSERT_EQ(0x08, payload.get()[0]);
    ASSERT_EQ(64, payload.getSize());
}


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
