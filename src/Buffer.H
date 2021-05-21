#ifndef __BUFFER_H__
#define __BUFFER_H__

class Buffer {
    public:
        Buffer(void* data, unsigned int sizeInBytes, unsigned int offsetInBytes = 0) {
            if (offsetInBytes > sizeInBytes) {
                this->_data = nullptr;
                this->_size = 0;
            }
            else {
                this->_data = (char*) data + offsetInBytes;
                this->_size = sizeInBytes - offsetInBytes;
            }
        }
        void* data() { return this->_data; }
        unsigned int size() { return this->_size; }
    private:
        unsigned int _size;
        void* _data;

        Buffer(Buffer& b) = delete;
        Buffer& operator = (const Buffer& b) = delete;
        Buffer(Buffer&& b) = delete;
        Buffer& operator = (const Buffer&& b) = delete;
};

#endif
