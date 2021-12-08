#include <gtest/gtest.h>
#include "Utils_test.H"
#include "Buffer_test.H"
#include "ICMPv4_test.H"
#include "IPv4_test.H"

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
