#include <gtest/gtest.h>
#include "../src/IP.H"
#include "mocks/NetDevMock.H"
#include "mocks/TunIfMock.H"
#include "data-test/Test_Frames.H"

class IP_Test: public ::testing::Test {
    protected:
        TunIfMock tunif { "tuntest" };
        NetDevMock netdev { tunif };
        IP ip { netdev };
};

TEST_F(IP_Test, validateCorrectInput) {
    NetBuf nb(123);
    Buffer buf(nb.data(), nb.size());
    ASSERT_EQ(IP::RetCode::OK, ip.input(nb, buf));
}

TEST_F(IP_Test, validateIncorrectInput) {
    NetBuf nb(1024);
    ASSERT_EQ(IP::RetCode::OK, ip.input(nb, Buffer(nb.data(), nb.size())));
    ASSERT_EQ(IP::RetCode::INVALID_INPUT_SIZE, ip.input(nb, Buffer(nb.data(), 2)));
}

TEST_F(IP_Test, validateCorrectInputSize) {
    NetBuf nb(100);
    ASSERT_EQ(0, ip.validateInputSize(nb, 80));
}

TEST_F(IP_Test, validateLessThanMinPacketSizeInput) {
    NetBuf nb(15);
    ASSERT_EQ(-2, ip.validateInputSize(nb, 15));
}

TEST_F(IP_Test, validateInputSizeSizeWhenPacketSizeIsLargerThanNetBuf) {
    NetBuf nb(100);
    ASSERT_EQ(-1, ip.validateInputSize(nb, 200));
}

TEST_F(IP_Test, validateHeaderInvalidIPVersion) {
    IP_Header iph;
    iph.version_headerlen = 0x65;
    Buffer packet((uint8_t *) &iph, sizeof(IP_Header));
    ASSERT_EQ(IP::RetCode::INVALID_IP_VERSION, ip.validateHeader(packet));
}

TEST_F(IP_Test, validateHeaderInvalidHeaderSize) {
    IP_Header iph;
    iph.version_headerlen = 0x47;
    Buffer packet((uint8_t *) &iph, sizeof(IP_Header));
    ASSERT_EQ(IP::RetCode::HEADER_LEN_DIFFERENT_FROM_20_BYTES, ip.validateHeader(packet));
}

TEST_F(IP_Test, validateTotalLenDoesntMatchWithReceivedPacketSize) {
    IP_Header iph;
    iph.version_headerlen = 0x45;
    iph.total_len = 50;
    Buffer packet((uint8_t *) &iph, sizeof(IP_Header));
    ASSERT_EQ(IP::RetCode::EXPECTED_PACKET_SIZE_DOESNT_MATCH_WITH_RECEIVED_PACKET_SIZE,
            ip.validateHeader(packet));
}

TEST_F(IP_Test, validateValidHeaderChecksum) {
    auto v = Test_Frames::valid_ip_header;
    Buffer packet(v.data(), v.size());
    ASSERT_EQ(IP::RetCode::OK,
            ip.validateHeaderChecksum(packet));
}

TEST_F(IP_Test, validateInvalidHeaderChecksum) {
    auto v = Test_Frames::invalid_ip_header;
    Buffer packet(v.data(), v.size());
    ASSERT_EQ(IP::RetCode::INVALID_HEADER_CHECKSUM,
            ip.validateHeaderChecksum(packet));
}
