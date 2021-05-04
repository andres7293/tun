#ifndef __NETBUF_H__
#define __NETBUF_H__

#include <stdint.h>

class NetBuf {
    public:
        NetBuf(uint16_t size) {
            this->size = size;
            this->p = new uint8_t[size];
        }
        ~NetBuf() {
            if (this->p != nullptr) {
                delete[] this->p;
            }
        }
        uint8_t* getBuf() { return this->p; }
        uint16_t getSize() { return this->size; }
    private:
        uint8_t* p;
        uint16_t size;

        NetBuf(const NetBuf &n) = delete;
        NetBuf& operator = (const NetBuf &n) = delete;
        NetBuf(const NetBuf &&n) = delete;
        NetBuf& operator = (const NetBuf &&n) = delete;
};

#endif
