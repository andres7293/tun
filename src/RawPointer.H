#ifndef __RAWPOINTER_H__
#define __RAWPOINTER_H__

#include <stdint.h>

class RawPointer {
    public:
        RawPointer(uint8_t* p, uint16_t size):
            p(p), _size(size) {}
        virtual ~RawPointer() {}
        uint8_t* get() { return this->p; }
        uint16_t size() { return this->_size; }
        uint8_t operator[] (int index) { return this->p[index]; }
    private:
        uint8_t* p;
        uint16_t _size;
};

#endif
