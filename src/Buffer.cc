#include "Buffer.H"

Buffer::Buffer(void* data, unsigned int sizeInBytes, unsigned int offsetInBytes) {
    if (offsetInBytes > sizeInBytes) {
        this->cancelBuffer();
        return;
    }
    this->_data = (char*) data + offsetInBytes;
    this->_size = sizeInBytes - offsetInBytes;
}

Buffer::Buffer(Buffer& buffer, int sizeLimit) {
    if (sizeLimit > buffer.size()) {
        this->cancelBuffer();
        return;
    }
    this->_data = buffer.data();
    this->_size = sizeLimit;
}

void* Buffer::data() {
    return this->_data; 
}

unsigned int Buffer::size() { 
    return this->_size; 
}

void Buffer::cancelBuffer() {
    this->_data = nullptr;
    this->_size = 0;
}
