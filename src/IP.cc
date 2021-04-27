#include "IP.H"
#include "Utils.H"
#include "ICMP.H"

int IP::ip_input(NetDev &netdev, uint8_t *ip_packet, uint16_t size) {
    if (IP::validate_ip_packet_size(size) != 0)
        return -1;
    if (IP::validate_header(ip_packet, size) != 0)
        return -2;
    IP_Header *iph = (IP_Header *) ip_packet;
    if (iph->getVersion() != 4)
        return -3;

    switch (iph->protocol) {
        case IP::ICMPV4_PROTOCOL:
            //ICMP::icmp_input(netdev, h, IP::getPayload(ip_packet, size), IP::getPayloadSize(ip_packet, size));
            break;
    }
    return 0;
}

int IP::validate_ip_packet_size(uint16_t ip_packet_size) {
    if (ip_packet_size < IP_Header::MIN_IP_HEADER_SIZE_BYTES)
        return -1;
    if (ip_packet_size > IP::MAX_IP_PACKET_SIZE)
        return -2;
    return 0;
}

int IP::validate_header(uint8_t *ip_packet, uint16_t size) {
    if (size < IP_Header::MIN_IP_HEADER_SIZE_BYTES)
        return -1;
    IP_Header *iph = (IP_Header *) ip_packet;
    if (iph->getHeaderLenInBytes() != IP_Header::MIN_IP_HEADER_SIZE_BYTES)
        return -2;
    //validate checksum header
    if (utils::checksum((void *) ip_packet, iph->getHeaderLenInBytes(), 0) != 0)
        return -3;
    //checks if total_len specified in header match with the current packet size
    if (size != utils::netToHostShort(iph->total_len))
        return -4;
    return 0;
}

uint8_t* IP::getPayload(uint8_t *ip_packet, uint16_t size) {
    uint8_t *payload = (uint8_t *) ip_packet + sizeof(IP_Header);
    return payload;
}

uint16_t IP::getPayloadSize(uint8_t *ip_packet, uint16_t size) {
    IP_Header *iph = (IP_Header *) ip_packet;
    return utils::hostToNetShort(iph->total_len) - iph->getHeaderLenInBytes();
}

uint8_t IP_Header::getVersion() {
    return ((this->version_headerlen & 0xf0) >> 4);
}

uint8_t IP_Header::getHeaderLen() {
    return (this->version_headerlen & 0x0f);
}

uint8_t IP_Header::getHeaderLenInBytes() {
    return this->getHeaderLen() * 4;
}

uint8_t IP_Header::getFlags() {
    return ((this->flags_fragoffset & 0xE000) >> 13);
}

uint8_t IP_Header::getFragmentOffset() {
    return (this->flags_fragoffset & 0x1FFF);
}

ostream& operator << (ostream& os, IP_Header &h) {
    os   << "IP_Header{"
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
