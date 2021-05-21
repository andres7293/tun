#include <gtest/gtest.h>
#include "../src/Packet.H"

TEST(Packet, testPacketSize) {
    NetBuf nb(1024);
    RawPointer header(nb.data(), 20);
    RawPointer payload(&nb.data()[20], 150);
    Packet packet(nb, header.size() + payload.size(), header, payload);
    ASSERT_EQ(header.size() + payload.size(), packet.getPacketSize());
}

TEST(Packet, testPacketSizeOutOfBounds) {
    NetBuf nb(12);
    RawPointer header(nullptr, 0);
    RawPointer payload(nullptr, 0);
    Packet packet(nb, 100, header, payload);
    ASSERT_EQ(-1, packet.boundCheck());
}

TEST(Packet, testHeaderOutOfBounds) {
    NetBuf nb(12);
    RawPointer header(nullptr, 15);
    RawPointer payload(nullptr, 0);
    Packet packet(nb, nb.size(), header, payload);
    ASSERT_EQ(-2, packet.boundCheck());
}

TEST(Packet, testPayloadOutOfBounds) {
    NetBuf nb(12);
    RawPointer header(nullptr, 2);
    RawPointer payload(nullptr, 124);
    Packet packet(nb, nb.size(), header, payload);
    ASSERT_EQ(-3, packet.boundCheck());
}

TEST(Packet, testPacketWithValidBounds) {
    NetBuf nb(120);
    RawPointer header(nullptr, 20);
    RawPointer payload(nullptr, 30);
    Packet packet(nb, header.size() + payload.size(), header, payload);
    ASSERT_EQ(0, packet.boundCheck());
}

TEST(Packet, testSuscriptOperator) {
    NetBuf nb(120);
    RawPointer header(nullptr, 20);
    RawPointer payload(nullptr, 30);
    Packet packet(nb, header.size() + payload.size(), header, payload);

    ASSERT_EQ(nb.data()[12], packet[12]);
}
