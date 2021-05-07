#include "NetBuf.H"
#include <string.h>

NetBuf::NetBuf(uint16_t size) {
    this->ctor(size);
}

NetBuf::~NetBuf() {
    if (this->p != nullptr) {
        delete[] this->p;
    }
}

NetBuf::NetBuf(const NetBuf &n) {
    ctor(n.size);
    memcpy((uint8_t *)this->p, (uint8_t *) n.p, n.size);
}

uint8_t* NetBuf::getBuf() {
    return this->p;
}

uint16_t NetBuf::getSize() {
    return this->size;
}

void NetBuf::ctor(uint16_t size) {
    this->size = size;
    this->p = new uint8_t[size];
}


StaticNetBuf::StaticNetBuf(MemPool *pool) {
    this->p = this->pool->alloc();
    if (this->p == nullptr) {
        throw StaticNetBufException("Can't alloc more memory in pool");
    }
}

StaticNetBuf::StaticNetBuf(StaticNetBuf &n) {
    this->pool = n.pool;
    this->p = n.pool->alloc();
    if (this->p == nullptr) {
        throw StaticNetBufException("Can't alloc more memory in pool");
    }
    memcpy((uint8_t *) this->p, (uint8_t *) n.getBuf(), n.getSize());
}

StaticNetBuf::~StaticNetBuf() {
    if (this->p != nullptr) {
        this->pool->free(this->p);
    }
}

uint8_t* StaticNetBuf::getBuf() {
    return (uint8_t *)this->p;
}

uint16_t StaticNetBuf::getSize() {
    return this->pool->getBlockSize();
}
