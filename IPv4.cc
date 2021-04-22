#include "IPv4.H"
#include "Utils.H"

int8_t IPv4_Header::validate_header(uint8_t *net_frame, uint8_t size) {
    if (size < IPv4_Header::MIN_IP_HEADER_SIZE_BYTES)
        return -1;
    IPv4_Header_t *h = (IPv4_Header_t *) net_frame;
    if (IPv4_Header::getHeaderLenInBytes(h) != IPv4_Header::MIN_IP_HEADER_SIZE_BYTES)
        return -2;
    if (IPv4_Header::validate_header_checksum(net_frame, size) != 0)
        return -3;
    return 0;
}

uint8_t IPv4_Header::getVersion(IPv4_Header_t *h) {
    return ((h->version_headerlen & 0xf0) >> 4);
}

uint8_t IPv4_Header::getHeaderLen(IPv4_Header_t *h) {
    return (h->version_headerlen & 0x0f);
}

uint8_t IPv4_Header::getHeaderLenInBytes(IPv4_Header_t *h) {
    return getHeaderLen(h) * 4;
}

uint8_t IPv4_Header::getFlags(IPv4_Header_t *h) {
    return ((h->flags_fragoffset & 0xE000) >> 13);
}

uint8_t IPv4_Header::getFragmentOffset(IPv4_Header_t *h) {
    return (h->flags_fragoffset & 0x1FFF);
}

/*The header must be validated in Network Endian Order (Big Endian)*/
uint16_t IPv4_Header::validate_header_checksum(uint8_t *header_frame, uint8_t header_size) {
    if (header_size < IPv4_Header::MIN_IP_HEADER_SIZE_BYTES) {
        return 1;
    }
    uint8_t num_blocks_of_16bits = IPv4_Header::MIN_IP_HEADER_SIZE_BYTES / 2;
    uint32_t u32_sum = 0;
    uint16_t *p = (uint16_t *) header_frame;
    for (uint32_t i = 0; i < num_blocks_of_16bits; i++) {
        u32_sum += p[i];
    }
    uint16_t carry = ((u32_sum & 0x000f0000) >> 16);
    uint16_t u16_sum = (u32_sum & 0x0000ffff);
    return ~(u16_sum + carry);
}

void IPv4_Header::convertHeaderToHostEndian(IPv4_Header_t *host, IPv4_Header_t *net) {
    host->version_headerlen = net->version_headerlen;
    host->tos               = net->tos;
    host->total_len         = utils::netToHostShort(net->total_len);
    host->id                = utils::netToHostShort(net->id);
    host->flags_fragoffset  = utils::netToHostShort(net->flags_fragoffset);
    host->ttl               = net->ttl;
    host->protocol          = net->protocol;
    host->header_checksum   = utils::netToHostShort(net->header_checksum);
    host->src_addr          = utils::netToHostLong(net->src_addr);
    host->dst_addr          = utils::netToHostLong(net->dst_addr);
}

void IPv4_Header::convertHeaderToNetEndian(IPv4_Header_t *net, IPv4_Header_t *host) {
    net->version_headerlen = host->version_headerlen;
    net->tos               = host->tos;
    net->total_len         = utils::hostToNetShort(host->total_len);
    net->id                = utils::hostToNetShort(host->id);
    net->flags_fragoffset  = utils::hostToNetShort(host->flags_fragoffset);
    net->ttl               = host->ttl;
    net->protocol          = host->protocol;
    net->header_checksum   = utils::hostToNetShort(host->header_checksum);
    net->src_addr          = utils::hostToNetLong(host->src_addr);
    net->dst_addr          = utils::hostToNetLong(host->dst_addr);
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
