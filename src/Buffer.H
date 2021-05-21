#ifndef __BUFFER_H__
#define __BUFFER_H__

class Buffer {
    public:
        Buffer(void* data, unsigned int sizeInBytes, unsigned int offsetInBytes = 0);
        void* data();
        unsigned int size();
    private:
        unsigned int _size;
        void* _data;

        Buffer(Buffer& b) = delete;
        Buffer& operator = (const Buffer& b) = delete;
        Buffer(Buffer&& b) = delete;
        Buffer& operator = (const Buffer&& b) = delete;
};

#endif
