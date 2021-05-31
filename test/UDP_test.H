#include <gtest/gtest.h>
#include "data-test/Test_Frames.H"
#include "../src/UDP.H"

class UPD_Test: public ::testing::Test {
    protected:
        UDP udp {};
};
