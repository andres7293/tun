#include <gtest/gtest.h>
#include "Utils_test.H"
#include "ICMP_test.H"
#include "IP_Header_test.H"
#include "Packet_test.H"
#include "IP_test.H"
#include "Buffer_test.H"

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
