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

class StaticNetBufException: public exception {
    public:
        StaticNetBufException(string msg): msg(msg) { }
        virtual const char* what() {
            return this->msg.c_str();
        }
    private:
        string msg;
};

class StaticNetBuf: public INetBuf {
    public:
        StaticNetBuf(MemPool *pool): pool(pool), p(nullptr) {
            this->p = this->pool->alloc();
            if (this->p == nullptr) {
                throw StaticNetBufException("Can't alloc more memory in pool");
            }
        };
        StaticNetBuf(StaticNetBuf &n) {
            this->pool = n.pool;
            this->p = n.pool->alloc();
            if (this->p == nullptr) {
                throw StaticNetBufException("Can't alloc more memory in pool");
            }
            memcpy((uint8_t *) this->p, (uint8_t *) n.getBuf(), n.getSize());
        }
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
