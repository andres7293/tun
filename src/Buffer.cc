#include "Buffer.H"

Buffer::Buffer(void* data, unsigned int sizeInBytes, unsigned int offsetInBytes) {
    if (offsetInBytes > sizeInBytes) {
        this->_data = nullptr;
        this->_size = 0;
    }
    else {
        this->_data = (char*) data + offsetInBytes;
        this->_size = sizeInBytes - offsetInBytes;
    }
}

void* Buffer::data() {
    return this->_data; 
}

unsigned int Buffer::size() { 
    return this->_size; 
}
