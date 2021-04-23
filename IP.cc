#include "IP.H"
#include "Utils.H"

int8_t IP::validate_ip_packet_size(uint16_t ip_packet_size) {
    if (ip_packet_size < IP_Header::MIN_IP_HEADER_SIZE_BYTES)
        return -1;
    if (ip_packet_size > IP::MAX_IP_PACKET_SIZE)
        return -2;
    return 0;
}

int8_t IP::validate_header(uint8_t *ip_packet, uint16_t size) {
    if (size < IP_Header::MIN_IP_HEADER_SIZE_BYTES)
        return -1;
    IP_Header_t *h = (IP_Header_t *) ip_packet;
    if (IP_Header::getHeaderLenInBytes(h) != IP_Header::MIN_IP_HEADER_SIZE_BYTES)
        return -2;
    if (IP::validate_header_checksum(ip_packet, size) != 0)
        return -3;
    //checks if total_len specified in header match with the current packet size
    if (size != utils::netToHostShort(h->total_len))
        return -4;
    return 0;
}

/*The header must be validated in Network Endian Order (Big Endian)*/
uint16_t IP::validate_header_checksum(uint8_t *header_frame, uint16_t size) {
    if (size < IP_Header::MIN_IP_HEADER_SIZE_BYTES) {
        return 1;
    }
    uint8_t num_blocks_of_16bits = IP_Header::MIN_IP_HEADER_SIZE_BYTES / 2;
    uint32_t u32_sum = 0;
    uint16_t *p = (uint16_t *) header_frame;
    for (uint32_t i = 0; i < num_blocks_of_16bits; i++) {
        u32_sum += p[i];
    }
    uint16_t carry = ((u32_sum & 0x000f0000) >> 16);
    uint16_t u16_sum = (u32_sum & 0x0000ffff);
    return ~(u16_sum + carry);
}

void IP::convertHeaderToHostEndian(IP_Header_t *host, IP_Header_t *net) {
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

void IP::convertHeaderToNetEndian(IP_Header_t *net, IP_Header_t *host) {
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

ostream& operator << (ostream& os, IP_Header_t &h) {
    os   << "IP_Header_t{"
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
