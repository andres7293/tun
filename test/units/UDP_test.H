#include <gtest/gtest.h>
#include "data-test/Test_Frames.H"

#include "../../src/UDP.H"
#include "../../src/Utils.H"

class UPD_Test: public ::testing::Test {
    protected:
        UDP udp {};
};

TEST_F(UPD_Test, testInvalidChecksum) {
    auto v = Test_Frames::udp_packet;
    Buffer payload(v.data(), v.size(), 20);
    UDP_Header * udph = (UDP_Header *) payload.data();
    IP_Header *iph = (IP_Header *) v.data();
    udph->src_port = utils::hostToNetShort(23);
    udph->dst_port = utils::hostToNetShort(34);
    ASSERT_EQ(UDP::RetCode::INVALID_CHECKSUM, udp.input(iph, payload));
}

TEST_F(UPD_Test, testPacketSizeLessThanMin) {
    std::array<uint8_t, 4> v {};
    Buffer payload{v.data(), v.size()};
    IP_Header *iph = (IP_Header *) v.data();
    ASSERT_EQ(UDP::RetCode::PACKET_SIZE_LESS_THAN_MIN_PACKET_SIZE, udp.input(iph, payload));
}

TEST_F(UPD_Test, testPacketSizeWithInvalidLengthInUDPHeader) {
    auto v = Test_Frames::udp_packet;
    IP_Header *iph = (IP_Header *) v.data();
    Buffer payload{v.data(), v.size(), 20};
    UDP_Header * udph = (UDP_Header *) payload.data();
    udph->length = utils::hostToNetShort(150);
    ASSERT_EQ(UDP::RetCode::EXPECTED_PACKET_SIZE_DOESNT_MATCH_WITH_RECEIVED_PACKET_SIZE, udp.input(iph, payload));
}
