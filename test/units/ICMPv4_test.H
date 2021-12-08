#include <gtest/gtest.h>
#include "../../src/IPv4.H"
#include "../../src/ICMPv4.H"
#include "../../src/Packet.H"
#include "data-test/Test_Frames.H"

class ICMPv4_test: public ::testing::Test
{
    protected:
        ICMPv4 icmp4 {};
};

TEST_F(ICMPv4_test, validICMPv4Frame)
{
    auto v = Test_Frames::icmp_echo_request;
    Packet packet { v.data(), v.size() };

    packet.setNetworkLayer(v.data(), 20);
    packet.setTransportLayer(v.data() + 20, v.size() - 20);

    ASSERT_EQ(0, icmp4.input(packet));
}
