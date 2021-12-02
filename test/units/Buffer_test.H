#include <bits/stdint-uintn.h>
#include <gtest/gtest.h>

#include "../../src/Buffer.H"

TEST(Buffer, testvalidBuffer) {
    std::array<char, 20> arr { "Hello world" };
    Buffer buf{arr.data(), arr.size()};
    ASSERT_EQ(arr.size(), buf.size());
    ASSERT_EQ(0, memcmp((char *)buf.data(), (char *) arr.data(), arr.size()));
}

TEST(Buffer, testLimitBufferSize) {
    std::array<char, 20> arr { "Hello world" };
    Buffer buf{arr.data(), 5};
    ASSERT_EQ(5, buf.size());
}

TEST(Buffer, testBufferOffset) {
    std::array<char, 20> arr { "Hello world" };
    Buffer buf{arr.data(), arr.size(), 4};
    ASSERT_EQ(arr.size() - 4, buf.size());
    ASSERT_EQ(0, memcmp((char *)buf.data(), (char *) &arr[4], buf.size()));
}

TEST(Buffer, testBufferOffsetGreaterThanBufferSize) {
    std::array<char, 20> arr { "Hello world" };
    Buffer buf{arr.data(), arr.size(), 50};
    ASSERT_EQ(nullptr, buf.data());
    ASSERT_EQ(0, buf.size());
}

TEST(Buffer, copyBufferWithCopiedBufferLimitedInSize) {
    std::array<char, 20> arr { "Hello world" };
    Buffer original{arr.data(), arr.size()};
    Buffer copy(original, 7);
    ASSERT_EQ(7, copy.size());
    ASSERT_EQ(0, memcmp((char *)copy.data(), (char *) original.data(), copy.size()));
}

TEST(Buffer, copyBufferWithCopiedBufferGreaterThanBufferSize) {
    std::array<char, 20> arr { "Hello world" };
    Buffer original{arr.data(), arr.size()};
    Buffer copy{original, 50};
    ASSERT_EQ(nullptr, copy.data());
    ASSERT_EQ(0, copy.size());
}

TEST(Buffer, testNullBuffer) {
    std::array<char, 20> arr { "Hello world" };
    Buffer buf{nullptr, arr.size()};
    ASSERT_EQ(true, buf.isNull());
    ASSERT_EQ(20, buf.size());

    Buffer nullBuf {};
    ASSERT_EQ(nullptr, nullBuf.data());
    ASSERT_EQ(0, nullBuf.size());
    ASSERT_EQ(true, nullBuf.isNull());
}

TEST(Buffer, testZeroSizeBuffer) {
    std::array<char, 20> arr { "Hello world" };
    Buffer buf{arr.data(), 0};
    ASSERT_EQ(false, buf.isNull());
    ASSERT_EQ(0, buf.size());
}

TEST(Buffer, testCreateWithOffset) {
    std::array<char, 12> arr { "Hello world" };
    Buffer original{arr.data(), arr.size()};
    Buffer bufWitOffset = Buffer::createWithOffset(original, 6);
    ASSERT_EQ(12 - 6, bufWitOffset.size());
    ASSERT_EQ(0, memcmp((char *)bufWitOffset.data(), (char *) &arr[6], bufWitOffset.size()));
}
