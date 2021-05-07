#ifndef __NETBUF_H__
#define __NETBUF_H__

#include <bits/stdint-uintn.h>
#include <stdint.h>
#include <exception>
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

class StaticNetBuf: public INetBuf {
    public:
        StaticNetBuf(MemPool *pool): pool(pool), p(nullptr) {
            this->p = this->pool->alloc();
        };
        ~StaticNetBuf() {
            if (this->p != nullptr) {
                this->pool->free(this->p);
            }
        }
        uint8_t* getBuf() {
            return (uint8_t *)this->p;
        }
        uint16_t getSize() {
            return this->pool->getBlockSize();
        }
    private:
        MemPool *pool;
        MemBlock *p;
};

#endif
