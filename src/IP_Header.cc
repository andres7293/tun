#include "IP_Header.H"

uint8_t IP_Header::getVersion(IP_Header_t *h) {
    return ((h->version_headerlen & 0xf0) >> 4);
}

uint8_t IP_Header::getHeaderLen(IP_Header_t *h) {
    return (h->version_headerlen & 0x0f);
}

uint8_t IP_Header::getHeaderLenInBytes(IP_Header_t *h) {
    return getHeaderLen(h) * 4;
}

uint8_t IP_Header::getFlags(IP_Header_t *h) {
    return ((h->flags_fragoffset & 0xE000) >> 13);
}

uint8_t IP_Header::getFragmentOffset(IP_Header_t *h) {
    return (h->flags_fragoffset & 0x1FFF);
}
