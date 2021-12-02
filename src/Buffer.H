#ifndef __BUFFER_H__
#define __BUFFER_H__

class Buffer {
    public:
        Buffer(): _data{nullptr}, _size{0} {}
        Buffer(void* data, unsigned int sizeInBytes, unsigned int offsetInBytes = 0);
        Buffer(Buffer& buffer, unsigned int sizeLimit);
        static Buffer createWithOffset(Buffer& buffer, unsigned int offsetInBytes);
        void* data();
        unsigned int size();
        bool isNull();
    private:
        unsigned int _size;
        void* _data;

        void cancelBuffer();
};

#endif
