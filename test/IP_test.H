#include <bits/stdint-uintn.h>
#include <gtest/gtest.h>
#include "../src/IP.H"
#include "../src/NetDev.H"
#include "../src/TunIf.H"

#include "mocks/NetDevMock.H"
#include "mocks/TunIfMock.H"

#include <vector>

using namespace std;

//Fixture
class IP_Test: public ::testing::Test {
    protected:
        void SetUp() override {
            this->tun = new TunIfMock("dummy");
            this->netdev = new NetDevMock(*this->tun);
        }
        void TearDown() override {
            delete this->tun;
            delete this->netdev;
        }

        TunIfMock *tun;
        NetDevMock *netdev;

        const vector<uint8_t> valid_frame = {0x45, 0x00, 0x00, 0x54, 0xf2, 0xc8, 0x40, 0x00, 0x40, 0x01, 0x49, 0xde, 0x7f, 0x00, 0x00, 0x01, 0x7f, 0x00, 0x00, 0x01, 0x08, 0x00, 0x4f, 0xff, 0x61, 0xfa, 0x00, 0x01, 0x8f, 0xe1, 0x7f, 0x60, 0x00, 0x00, 0x00, 0x00, 0x76, 0xf0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37};
};

TEST_F(IP_Test, ip_input_validPacket) {
    NetBuf nb(valid_frame);
    IP_Packet goodPacket(&nb);
    ASSERT_EQ(0, IP::ip_input(*netdev, goodPacket));
}

TEST_F(IP_Test, ip_input_badHeader) {
    vector<uint8_t> zero(20);
    NetBuf nb(zero);
    IP_Packet badHeader(&nb);
    ASSERT_EQ(-2, IP::ip_input(*netdev, badHeader));
}

TEST_F(IP_Test, ip_input_zeroSizePacket) {
    vector<uint8_t> zero(0);
    NetBuf nb(zero);
    IP_Packet zeroSizePacket(&nb);
    ASSERT_EQ(-1, IP::ip_input(*netdev, zeroSizePacket));
}

TEST_F(IP_Test, validateZeroSizePacket) {
    ASSERT_EQ(-1, IP::validate_ip_packet_size(0));
}

TEST_F(IP_Test, validatePacketLesserThanHeaderSize) {
    ASSERT_EQ(-1, IP::validate_ip_packet_size(19));
}

TEST(IP, validateHeaderSizePacket) {
    ASSERT_EQ(0, IP::validate_ip_packet_size(20));
}

TEST_F(IP_Test, validateValidHeader) {
    NetBuf nb(valid_frame);
    IP_Packet goodPacket(&nb);
    ASSERT_EQ(0, IP::validate_header(goodPacket));
}

TEST_F(IP_Test, validateHeaderOfZeroSizePacket) {
    vector<uint8_t> zero;
    NetBuf nb(zero);
    IP_Packet zeroSizePacket(&nb);
    ASSERT_EQ(-1, IP::validate_header(zeroSizePacket));
}

TEST_F(IP_Test, validateHeaderWithBadHeaderLen) {
    NetBuf nb(valid_frame);
    nb.getBuf()[0] = 0x46;
    IP_Packet badHeader(&nb);
    ASSERT_EQ(-2, IP::validate_header(badHeader));
}

TEST_F(IP_Test, validateHeaderWithBadChecksum) {
    NetBuf nb(valid_frame);
    nb.getBuf()[1] = 1;
    IP_Packet badHeader(&nb);
    ASSERT_EQ(-3, IP::validate_header(badHeader));
}

TEST_F(IP_Test, validatePacketThatDoesntMatchWithSizeInHeader) {
    vector<uint8_t> v = valid_frame;
    v.resize(1024);
    NetBuf nb(v);
    IP_Packet tooLargePacket(&nb);
    ASSERT_EQ(-4, IP::validate_header(tooLargePacket));
}

TEST_F(IP_Test, getValidPayload) {
    NetBuf nb(valid_frame);
    IP_Packet packet(&nb);
    IP_Payload payload = IP::getPayload(packet);
    ASSERT_EQ(0x08, payload.get()[0]);
    ASSERT_EQ(64, payload.getSize());
}
