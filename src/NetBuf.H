#ifndef __NETBUF_H__
#define __NETBUF_H__

#include <bits/stdint-uintn.h>
#include <stdint.h>
#include <string.h>

class NetBuf {
    public:
        NetBuf(uint16_t size) {
            this->ctor(size);
        }
        ~NetBuf() {
            if (this->p != nullptr) {
                delete[] this->p;
            }
        }
        NetBuf(const NetBuf &n) {
            ctor(n.size);
            memcpy((uint8_t *)this->p, (uint8_t *) n.p, n.size);
        }
        uint8_t* getBuf() { return this->p; }
        uint16_t getSize() { return this->size; }
    private:
        uint8_t* p;
        uint16_t size;

        void ctor(uint16_t size) {
            this->size = size;
            this->p = new uint8_t[size];
        }

        NetBuf& operator = (const NetBuf &n) = delete;
        NetBuf(const NetBuf &&n) = delete;
        NetBuf& operator = (const NetBuf &&n) = delete;
};

#endif
