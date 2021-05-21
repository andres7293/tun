#ifndef __NETBUFALLOCATOR_H__
#define __NETBUFALLOCATOR_H__

#include "NetBuf.H"
#include <memory>

class INetBufAllocator {
    public:
        virtual std::shared_ptr<INetBuf> alloc(uint16_t bufSize) = 0;
    private:
};

class NetBufAllocator: public INetBufAllocator {
    public:
        std::shared_ptr<INetBuf> alloc(uint16_t bufSize) { 
            return std::shared_ptr<INetBuf>(new NetBuf(bufSize));
        }
};

#endif
