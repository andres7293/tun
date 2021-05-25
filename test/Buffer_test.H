#include <bits/stdint-uintn.h>
#include <gtest/gtest.h>
#include "../src/Buffer.H"

TEST(Buffer, testvalidBuffer) {
    std::array<char, 20> arr { "Hello world" };
    Buffer buf(arr.data(), arr.size());
    ASSERT_EQ(arr.size(), buf.size());
    ASSERT_EQ(arr.data(), buf.data());
}

TEST(Buffer, testLimitBufferSize) {
    std::array<char, 20> arr { "Hello world" };
    Buffer buf(arr.data(), 5);
    ASSERT_EQ(5, buf.size());
}

TEST(Buffer, testBufferOffset) {
    std::array<char, 20> arr { "Hello world" };
    Buffer buf(arr.data(), arr.size(), 4);

    ASSERT_EQ(arr.size() - 4, buf.size());
    char *car = (char*) buf.data();
    ASSERT_EQ('o', car[0]);
    ASSERT_EQ('w', car[2]);
}

TEST(Buffer, testBufferOffsetGreaterThanBufferSize) {
    std::array<char, 20> arr { "Hello world" };
    Buffer buf(arr.data(), arr.size(), 50);
    ASSERT_EQ(NULL, buf.data());
    ASSERT_EQ(0, buf.size());
}

TEST(Buffer, copyBufferWithCopiedBufferLimitedInSize) {
    std::array<char, 20> arr { "Hello world" };
    Buffer original(arr.data(), arr.size());
    Buffer copy(original, 7);
    char* car = (char *) copy.data();
    ASSERT_EQ(7, copy.size());
    ASSERT_EQ('H', car[0]);
}

TEST(Buffer, copyBufferWithCopiedBufferGreaterThanBufferSize) {
    std::array<char, 20> arr { "Hello world" };
    Buffer original(arr.data(), arr.size());
    Buffer copy(original, 50);

    ASSERT_EQ(NULL, copy.data());
    ASSERT_EQ(0, copy.size());
}

TEST(Buffer, testNullBuffer) {
    std::array<char, 20> arr { "Hello world" };
    Buffer buf(nullptr, arr.size());

    ASSERT_EQ(true, buf.isNull());
    ASSERT_EQ(20, buf.size());
}

TEST(Buffer, testZeroSizeBuffer) {
    std::array<char, 20> arr { "Hello world" };
    Buffer buf(arr.data(), 0);

    ASSERT_EQ(false, buf.isNull());
    ASSERT_EQ(0, buf.size());
}

TEST(Buffer, testCreateWithOffset) {
    std::array<char, 12> arr { "Hello world" };
    Buffer buffer(arr.data(), arr.size());
    Buffer bufWitOffset = Buffer::createWithOffset(buffer, 6);
    ASSERT_EQ(12 - 6, bufWitOffset.size());
    char *car = (char *) bufWitOffset.data();
    ASSERT_EQ('w', car[0]);
    ASSERT_EQ('o', car[1]);
}
