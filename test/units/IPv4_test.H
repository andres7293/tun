#include <gtest/gtest.h>
#include "../../src/IPv4.H"
#include "../../src/Buffer.H"
#include "data-test/Test_Frames.H"

class IPv4_Test: public ::testing::Test
{
    protected:
        IPv4 ipv4 {};
};

TEST_F(IPv4_Test, validIPv4Frame)
{
    auto v = Test_Frames::icmp_echo_request;
    Packet packet { v.data(), v.size() };

    ASSERT_EQ(0, ipv4.input(packet));

    ASSERT_EQ(20, packet.getNetworkLayer().size());
    ASSERT_EQ(v.size() - 20, packet.getTransportLayer().size());
}

TEST_F(IPv4_Test, PacketTooShort)
{
    const int SIZE = 19;
    auto v = std::make_unique<uint8_t[]>(SIZE);
    Packet packet { v.get(), SIZE };

    ASSERT_EQ(-1, ipv4.input(packet));
}

TEST_F(IPv4_Test, PacketTooLarge)
{
    const int SIZE = 65535 + 1;
    auto v = std::make_unique<uint8_t[]>(SIZE);
    Packet packet { v.get(), SIZE };

    ASSERT_EQ(-2, ipv4.input(packet));
}

TEST_F(IPv4_Test, invalidIPVersion)
{
    //Generate packet with wrong ip version
    IPv4Header iph;
    iph.version_headerlen = 0x65;
    const int SIZE = sizeof(IPv4Header) + 20;
    const auto v = std::make_unique<uint8_t[]>(SIZE);
    memcpy((uint8_t *) v.get(), (uint8_t *) &iph, sizeof(IPv4Header));

    Packet packet { v.get(), SIZE };
    ASSERT_EQ(-3, ipv4.input(packet));
}

TEST_F(IPv4_Test, packetWithWrongHeaderLen)
{
    //Generate packet with wrong ip header len
    IPv4Header iph;
    iph.version_headerlen = 0x47;
    const int SIZE = sizeof(IPv4Header) + 20;
    const auto v = std::make_unique<uint8_t[]>(SIZE);
    memcpy((uint8_t *) v.get(), (uint8_t *) &iph, sizeof(IPv4Header));

    Packet packet { v.get(), SIZE };
    ASSERT_EQ(-4, ipv4.input(packet));
}

TEST_F(IPv4_Test, totalLenDoesNotMatchWithReceivedPacketSize)
{
    auto v = Test_Frames::icmp_echo_request;
    IPv4Header *iph = (IPv4Header*) v.data();
    iph->version_headerlen = 0x45;
    iph->total_len = 50;
    Packet packet { v.data(), v.size() };
    ASSERT_EQ(-5, ipv4.input(packet));
}

TEST_F(IPv4_Test, invalidIPv4Checksum)
{
    auto v = Test_Frames::icmp_echo_request;
    IPv4Header *iph = (IPv4Header*) v.data();
    iph->header_checksum = 0xfa;
    Packet packet { v.data(), v.size() };
    ASSERT_EQ(-6, ipv4.input(packet));
}

TEST_F(IPv4_Test, IPv4AddressConversions)
{
    IPv4Addr localhost { "127.0.0.1" };
    IPv4Addr loopback { "127.0.0.0" };
    IPv4Addr private_use { "10.0.0.0" };
    IPv4Addr local_network { "192.168.1.204" };

    ASSERT_EQ("127.0.0.1", localhost.toString());
    ASSERT_EQ(0x7f000001, localhost.getAddress());

    ASSERT_EQ("127.0.0.0", loopback.toString());
    ASSERT_EQ(0x7f000000, loopback.getAddress());

    ASSERT_EQ("10.0.0.0", private_use.toString());
    ASSERT_EQ(0x0A000000, private_use.getAddress());

    ASSERT_EQ("192.168.1.204", local_network.toString());
    ASSERT_EQ(0xc0a801cc, local_network.getAddress());
}
