#ifndef __NETBUF_H__
#define __NETBUF_H__

#include <stdint.h>

class NetBuf {
    public:
        NetBuf(uint8_t*p, uint16_t size): p(p), size(size) {};
    private:
        uint8_t* p;
        uint16_t size;

        NetBuf(const NetBuf &n) = delete;
        NetBuf& operator = (const NetBuf &n) = delete;
        NetBuf(const NetBuf &&n) = delete;
        NetBuf& operator = (const NetBuf &&n) = delete;
};

#endif
