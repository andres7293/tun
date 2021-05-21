#ifndef __NETBUF_H__
#define __NETBUF_H__

#include <stdint.h>
#include <vector>
#include <exception>
#include <string.h>

class INetBuf {
    public:
        virtual ~INetBuf() {};
        virtual uint8_t* data() = 0;
        virtual uint16_t size() = 0;
};

class NetBuf: public INetBuf {
    public:
        NetBuf(uint8_t *data, uint16_t size);
        NetBuf(uint16_t size);
        ~NetBuf();
        uint8_t* data();
        uint16_t size();
    private:
        uint8_t* p;
        uint16_t _size;

        void ctor(uint16_t size);

        NetBuf(NetBuf &n) = delete;
        NetBuf& operator = (const NetBuf &n) = delete;
        NetBuf(const NetBuf &&n) = delete;
        NetBuf& operator = (const NetBuf &&n) = delete;
};

#endif
