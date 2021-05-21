#include "NetBuf.H"
#include <string.h>
#include <iostream>

NetBuf::NetBuf(uint8_t *data, uint16_t size) {
    this->ctor(size);
    memcpy((uint8_t *) this->p, (uint8_t *) data, this->_size);
}

NetBuf::NetBuf(uint16_t size) {
    this->ctor(size);
}

NetBuf::~NetBuf() {
    if (this->p != nullptr) {
        delete[] this->p;
    }
}

uint8_t* NetBuf::data() {
    return this->p;
}

uint16_t NetBuf::size() {
    return this->_size;
}

void NetBuf::ctor(uint16_t size) {
    this->_size = size;
    this->p = new uint8_t[size];
}
