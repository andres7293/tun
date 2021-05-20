#include <gtest/gtest.h>
#include <sys/types.h>
#include "../src/RawPointer.H"

TEST(RawPointer, testRawPointer) {
    int size = 234;
    uint8_t *buf = new uint8_t[size];
    RawPointer rptr(buf, size);
    ASSERT_EQ(size, rptr.size());
    ASSERT_EQ(buf, rptr.get());
    delete[] buf;
}
