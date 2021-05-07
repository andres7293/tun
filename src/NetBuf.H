#ifndef __NETBUF_H__
#define __NETBUF_H__

#include <stdint.h>

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

#endif
