#include "IPv4.H"
#include <cstdint>

void IP_Header::parse(uint8_t *net_frame) {
    IPv4_Header_t *raw = (IPv4_Header_t *) net_frame;

    this->header.version_headerlen = raw->version_headerlen;
    this->header.tos               = raw->tos;
    this->header.total_len         = netToHostShort(raw->total_len);
    this->header.id                = netToHostShort(raw->id);
    this->header.flags_fragoffset  = netToHostShort(raw->flags_fragoffset);
    this->header.ttl               = raw->ttl;
    this->header.protocol          = raw->protocol;
    this->header.header_checksum   = netToHostShort(raw->header_checksum);
    this->header.src_addr          = netToHostLong(raw->src_addr);
    this->header.dst_addr          = netToHostLong(raw->dst_addr);
}

uint8_t IP_Header::getVersion() {
    return ((this->header.version_headerlen & 0xf0) >> 4);
}

uint8_t IP_Header::getHeaderLen() {
    return (this->header.version_headerlen & 0x0f);
}

uint8_t IP_Header::getFlags() {
    return ((this->header.flags_fragoffset & 0xE000) >> 13);
}

uint8_t IP_Header::getFragmentOffset() {
    return (this->header.flags_fragoffset & 0x1FFF);
}

IPv4_Protocol IP_Header::getProtocol() {
    if (this->header.protocol == 0x01) {
        return IPv4_Protocol::ICMP;
    }
    else {
        return IPv4_Protocol::UNKNOW;
    }
}

uint16_t netToHostShort(uint16_t val) {
    uint16_t result;

    uint8_t *dest = (uint8_t *) &result;
    uint8_t *src  = (uint8_t *) &val;

    dest[0] = src[1];
    dest[1] = src[0];
    return result;
}

uint32_t netToHostLong(uint32_t val) {
    uint32_t result;

    uint8_t *dest = (uint8_t *) &result;
    uint8_t *src  = (uint8_t *) &val;

    dest[0] = src[3];
    dest[1] = src[2];
    dest[2] = src[1];
    dest[3] = src[0];

    return result;
}

ostream& operator << (ostream& os, IPv4_Header_t &h) {
    os   << "IPv4_Header_t{"
         << "version_headerlen=0x" << hex << (int) h.version_headerlen << dec
         << ",tos=0x"              << hex << (int) h.tos               << dec
         << ",total_len=0x"        << hex << (int) h.total_len         << dec
         << ",id=0x"               << hex << (int) h.id                << dec
         << ",flags_fragoffset=0x" << hex << (int) h.flags_fragoffset  << dec
         << ",ttl=0x"              << hex << (int) h.ttl               << dec
         << ",protocol=0x"         << hex << (int) h.protocol          << dec
         << ",header_checksum=0x"  << hex << (int) h.header_checksum   << dec
         << ",src_addr=0x"         << hex << (int) h.src_addr          << dec
         << ",dst_addr=0x"         << hex << (int) h.dst_addr          << dec
         << "}";
    return os;
}
