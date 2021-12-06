#include "Buffer.H"
#include <cstring>

Buffer::Buffer(void* data, unsigned int sizeInBytes, unsigned int offsetInBytes) {
    if (offsetInBytes > sizeInBytes) {
        this->cancelBuffer();
        return;
    }
    this->_data = (char*) data + offsetInBytes;
    this->_size = sizeInBytes - offsetInBytes;
}

Buffer::Buffer(Buffer& buffer, unsigned int sizeLimit) {
    if (sizeLimit > buffer.size()) {
        this->cancelBuffer();
        return;
    }
    this->_data = buffer.data();
    this->_size = sizeLimit;
}

Buffer Buffer::createWithOffset(Buffer buffer, unsigned int offsetInBytes) {
    return Buffer{buffer.data(), buffer.size(), offsetInBytes};
}

void* Buffer::data() {
    return this->_data; 
}

unsigned int Buffer::size() { 
    return this->_size; 
}

bool Buffer::isNull() {
    if (this->data() == nullptr) {
        return true;
    }
    return false;
}

void Buffer::cancelBuffer() {
    this->_data = nullptr;
    this->_size = 0;
}

bool Buffer::operator == (Buffer& b) {
    if (this->size() != b.size()) {
        return false;
    }
    if (0 != memcmp(
                this->data(),
                b.data(),
                this->size()
                )
       ) {
        return false;
    }
    return true;
}
