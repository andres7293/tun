#include <gtest/gtest.h>
#include "../src/ICMP.H"
#include "data-test/Test_Frames.H"

class ICMP_Test: public ::testing::Test {
    protected:
        ICMP icmp {};
};

TEST_F(ICMP_Test, validateHeaderSizeTooShort) {
    std::array<uint8_t, 1> a;
    Buffer payload(a.data(), a.size());
    ASSERT_EQ(ICMP::RetCode::HEADER_SIZE_TOO_SHORT, icmp.input(payload));
}

TEST_F(ICMP_Test, validateCorrectHeaderChecksum) {
    auto v = Test_Frames::icmp_echo_request;
    Buffer payload(v.data(), v.size(), 20);
    ASSERT_EQ(ICMP::RetCode::ECHO_REPLY, icmp.input(payload));
}

TEST_F(ICMP_Test, validateIncorrectHeaderChecksum) {
    auto v = Test_Frames::invalid_icmp_echo_request;
    Buffer payload(v.data(), v.size(), 20);
    ASSERT_EQ(ICMP::RetCode::CHECKSUM_ERROR, icmp.input(payload));
}
