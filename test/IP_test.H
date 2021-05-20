#include <bits/stdint-uintn.h>
#include <gtest/gtest.h>
#include "../src/IP.H"
#include "../src/NetDev.H"
#include "../src/TunIf.H"

#include "mocks/NetDevMock.H"
#include "mocks/TunIfMock.H"

#include "data-test/Test_Frames.H"

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

};

TEST_F(IP_Test, ip_input_validPacket) {
    NetBuf nb(Test_Frames::valid_icmp);
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
    NetBuf nb(Test_Frames::valid_icmp);
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
    NetBuf nb(Test_Frames::valid_icmp);
    nb.getBuf()[0] = 0x46;
    IP_Packet badHeader(&nb);
    ASSERT_EQ(-2, IP::validate_header(badHeader));
}

TEST_F(IP_Test, validateHeaderWithBadChecksum) {
    NetBuf nb(Test_Frames::valid_icmp);
    nb.getBuf()[1] = 1;
    IP_Packet badHeader(&nb);
    ASSERT_EQ(-3, IP::validate_header(badHeader));
}

TEST_F(IP_Test, validatePacketThatDoesntMatchWithSizeInHeader) {
    vector<uint8_t> v = Test_Frames::valid_icmp;
    v.resize(1024);
    NetBuf nb(v);
    IP_Packet tooLargePacket(&nb);
    ASSERT_EQ(-4, IP::validate_header(tooLargePacket));
}

TEST_F(IP_Test, getValidPayload) {
    NetBuf nb(Test_Frames::valid_icmp);
    IP_Packet packet(&nb);
    IP_Payload payload = IP::getPayload(packet);
    ASSERT_EQ(0x08, payload.get()[0]);
    ASSERT_EQ(64, payload.getSize());
}
