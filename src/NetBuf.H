#ifndef __NETBUF_H__
#define __NETBUF_H__

#include <bits/stdint-uintn.h>
#include <stdint.h>
#include <exception>
#include <string.h>
#include "MemoryPool.H"
#include "Config.H"

class INetBuf {
    public:
        virtual ~INetBuf() {};
        virtual uint8_t* getBuf() = 0;
        virtual uint16_t getSize() = 0;
};

class NetBuf: public INetBuf {
    public:
        NetBuf(uint16_t size);
        ~NetBuf();
        NetBuf(const NetBuf &n);
        uint8_t* getBuf();
        uint16_t getSize();
    private:
        uint8_t* p;
        uint16_t size;

        void ctor(uint16_t size);

        NetBuf& operator = (const NetBuf &n) = delete;
        NetBuf(const NetBuf &&n) = delete;
        NetBuf& operator = (const NetBuf &&n) = delete;
};

template <uint16_t N>
class StaticNetBuf: public INetBuf {
    public:
        StaticNetBuf() {}
        ~StaticNetBuf() {}
        StaticNetBuf(StaticNetBuf &n) {
            memcpy((uint8_t *) this->p, (uint8_t *) n.getBuf(), N);
        }
        uint8_t* getBuf() { return this->p; };
        uint16_t getSize() { return N; }
    private:
        uint8_t p[N];
};

#endif
