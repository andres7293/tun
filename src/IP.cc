#include "IP.H"
#include "Utils.H"
#include "ICMP.H"

int IP::ip_input(NetDev &netdev, IP_Packet &packet) {
    if (IP::validate_ip_packet_size(packet.getSize()) != 0)
        return -1;
    if (IP::validate_header(packet) != 0)
        return -2;
    IP_Header *iph = (IP_Header *) packet.get();
    if (iph->getVersion() != 4)
        return -3;

    switch (iph->protocol) {
        case IP::ICMPV4_PROTOCOL:
            ICMP::icmp_input(netdev, packet);
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

int IP::validate_header(IP_Packet &packet) {
    if (packet.getSize() < IP_Header::MIN_IP_HEADER_SIZE_BYTES)
        return -1;
    IP_Header *iph = (IP_Header *) packet.get();
    if (iph->getHeaderLenInBytes() != IP_Header::MIN_IP_HEADER_SIZE_BYTES)
        return -2;
    //validate checksum header
    if (utils::checksum((void *) packet.get(), iph->getHeaderLenInBytes(), 0) != 0)
        return -3;
    //checks if total_len specified in header match with the current packet size
    if (packet.getSize() != utils::netToHostShort(iph->total_len))
        return -4;
    return 0;
}

IP_Payload IP::getPayload(IP_Packet &packet) {
    uint16_t hsize = sizeof(IP_Header);
    return IP_Payload((uint8_t *) packet.get() + hsize, packet.getSize() - hsize);
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
