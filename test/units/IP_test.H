#include <gtest/gtest.h>
#include "mocks/NetDevMock.H"
#include "mocks/TunIfMock.H"
#include "data-test/Test_Frames.H"

#include "../../src/IP.H"

class IP_Test: public ::testing::Test {
    protected:
        TunIfMock tunif { "tuntest" };
        NetDevMock netdev { tunif };
        IP ip { netdev };
};

TEST_F(IP_Test, validIPInputFrame) {
    auto v = Test_Frames::icmp_echo_request;
    NetBuf nb{v.data(), v.size()};
    ASSERT_EQ(IP::RetCode::OK,
            ip.input(nb, nb.size()));
}

TEST_F(IP_Test, validateCorrectInputSize) {
    NetBuf nb{100};
    ASSERT_EQ(IP::RetCode::OK, ip.validateInputSize(nb, 80));
}

TEST_F(IP_Test, validateLessThanMinPacketSizeInput) {
    NetBuf nb{15};
    ASSERT_EQ(IP::RetCode::PACKET_SIZE_LESS_THAN_MIN_PACKET_SIZE,
            ip.validateInputSize(nb, 15));
}

TEST_F(IP_Test, validateInputSizeSizeWhenPacketSizeIsLargerThanNetBuf) {
    NetBuf nb{100};
    ASSERT_EQ(IP::RetCode::PACKET_SIZE_GREATER_THAN_NETBUF_SIZE, 
            ip.validateInputSize(nb, 200));
}

TEST_F(IP_Test, validateHeaderInvalidIPVersion) {
    IP_Header iph;
    iph.version_headerlen = 0x65;
    Buffer packet{(uint8_t *) &iph, sizeof(IP_Header)};
    ASSERT_EQ(IP::RetCode::INVALID_IP_VERSION, ip.validateHeader(packet));
}

TEST_F(IP_Test, validateHeaderInvalidHeaderSize) {
    IP_Header iph;
    iph.version_headerlen = 0x47;
    Buffer packet{(uint8_t *) &iph, sizeof(IP_Header)};
    ASSERT_EQ(IP::RetCode::HEADER_LEN_DIFFERENT_FROM_20_BYTES, ip.validateHeader(packet));
}

TEST_F(IP_Test, validateTotalLenDoesntMatchWithReceivedPacketSize) {
    IP_Header iph;
    iph.version_headerlen = 0x45;
    iph.total_len = 50;
    Buffer packet{(uint8_t *) &iph, sizeof(IP_Header)};
    ASSERT_EQ(IP::RetCode::EXPECTED_PACKET_SIZE_DOESNT_MATCH_WITH_RECEIVED_PACKET_SIZE,
            ip.validateHeader(packet));
}

TEST_F(IP_Test, validateValidHeaderChecksum) {
    auto v = Test_Frames::valid_ip_header;
    Buffer packet{v.data(), v.size()};
    ASSERT_EQ(IP::RetCode::OK,
            ip.validateHeaderChecksum(packet));
}

TEST_F(IP_Test, validateInvalidHeaderChecksum) {
    auto v = Test_Frames::invalid_ip_header;
    Buffer packet{v.data(), v.size()};
    ASSERT_EQ(IP::RetCode::INVALID_HEADER_CHECKSUM,
            ip.validateHeaderChecksum(packet));
}

TEST_F(IP_Test, IPAddr) {
    IPAddr localhost { "127.0.0.1" };
    IPAddr loopback { "127.0.0.0" };
    IPAddr private_use { "10.0.0.0" };

    ASSERT_EQ("127.0.0.1", localhost.toString());
    ASSERT_EQ(0x7f000001, localhost.getAddress());

    ASSERT_EQ("127.0.0.0", loopback.toString());
    ASSERT_EQ(0x7f000000, loopback.getAddress());

    ASSERT_EQ("10.0.0.0", private_use.toString());
    ASSERT_EQ(0x0A000000, private_use.getAddress());
}
