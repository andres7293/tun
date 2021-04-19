#include "IPv4.H"
#include <cstdint>

IPv4::IPv4(const uint8_t *net_frame) {
    IPv4_Header_t *raw = (IPv4_Header_t *) net_frame;

    this->ip_header.version_headerlen = raw->version_headerlen;
    this->ip_header.tos               = raw->tos;
    this->ip_header.total_len         = netToHostShort(raw->total_len);
    this->ip_header.id                = netToHostShort(raw->id);
    this->ip_header.flags_fragoffset  = netToHostShort(raw->flags_fragoffset);
    this->ip_header.ttl               = raw->ttl;
    this->ip_header.protocol          = raw->protocol;
    this->ip_header.header_checksum   = netToHostShort(raw->header_checksum);
    this->ip_header.src_addr          = netToHostLong(raw->src_addr);
    this->ip_header.dst_addr          = netToHostLong(raw->dst_addr);
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
    os << "IPv4_Header_t{"
        << "version=0x"          << hex << (int) ((h.version_headerlen & 0xf0) >> 4)               << dec
        << ",headerLen=0x"       << hex << (int)(h.version_headerlen & 0x0f)                       << dec
        << ",tos=0x"             << hex << (int) h.total_len                                       << dec
        << ",id=0x"              << hex << (int) h.id                                              << dec
        << ",flags=0x"           << hex << (int) ((h.flags_fragoffset & 0b1110000000000000) >> 13) << dec
        << ",fragment_offset=0x" << hex << (int) (h.flags_fragoffset & 0b0001111111111111)         << dec
        << ",ttl=0x"             << hex << (int) h.ttl                                             << dec
        << ",protocol=0x"        << hex << (int) h.protocol                                        << dec
        << ",header_checksum=0x" << hex << (int) h.header_checksum                                 << dec
        << ",src_addr=0x"        << hex << (int) h.src_addr                                        << dec
        << ",dst_addr=0x"        << hex << (int) h.dst_addr                                        << dec
        << "}"
        ;
    return os;
}
