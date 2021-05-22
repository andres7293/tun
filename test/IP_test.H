#include <gtest/gtest.h>
#include "../src/IP.H"
#include "mocks/NetDevMock.H"
#include "mocks/TunIfMock.H"

class IP_Test: public ::testing::Test {
    protected:
        TunIfMock tunif { "tuntest" };
        NetDevMock netdev { tunif };
        IP ip { netdev };
};

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
