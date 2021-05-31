#include "IP.H"
#include "Utils.H"
#include "ICMP.H"

IP::RetCode IP::input(INetBuf& nbuf, uint16_t packetSize) {
    IP::RetCode ret;
    Buffer packet(nbuf.data(), packetSize);
    ret = this->validateInputSize(nbuf, packetSize);
    if (ret != IP::RetCode::OK)
        return ret;
    ret = this->validateHeader(packet);
    if (ret != IP::RetCode::OK)
        return ret;
    ret = this->validateHeaderChecksum(packet);
    if (ret != IP::RetCode::OK)
        return ret;
    IP_Header *iph = (IP_Header *) packet.data();
    if (iph->protocol == ICMPV4_PROTOCOL) {
        ICMP icmp {};
        icmp.input(Buffer::createWithOffset(packet, sizeof(IP_Header)));
        this->icmp_output(iph, packet);
    }
    else if (iph->protocol == UDPV4_PROTOCOL) {
    }
    return IP::RetCode::OK;
}

IP::RetCode IP::icmp_output(IP_Header *iph, Buffer packet) {
    uint32_t src = iph->src_addr;
    uint32_t dst = iph->dst_addr;
    iph->src_addr = dst;
    iph->dst_addr = src;
    iph->header_checksum = this->generate_header_checksum(iph);
    this->netdev.write((uint8_t *) packet.data(), packet.size());
    return IP::RetCode::OK;
}

IP::RetCode IP::validateInputSize(INetBuf& nbuf, uint16_t packetSize) {
    if (packetSize > nbuf.size()) {
        return IP::RetCode::PACKET_SIZE_GREATER_THAN_NETBUF_SIZE;
    }
    if (packetSize < IP::MIN_IP_PACKET_SIZE) {
        return IP::RetCode::PACKET_SIZE_LESS_THAN_MIN_PACKET_SIZE;
    }
    if (packetSize > IP::MAX_IP_PACKET_SIZE) {
        return IP::RetCode::PACKET_SIZE_GREATER_THAN_MAX_PACKET_SIZE;
    }
    return IP::RetCode::OK;
}

IP::RetCode IP::validateHeader(Buffer packet) {
    IP_Header *iph = (IP_Header *) packet.data();
    if (iph->getVersion() != IP::IPV4_VERSION) {
        return IP::RetCode::INVALID_IP_VERSION;
    }
    if (iph->getHeaderLenInBytes() != IP::MIN_IP_PACKET_SIZE) {
        return IP::RetCode::HEADER_LEN_DIFFERENT_FROM_20_BYTES;
    }
    uint16_t expectedPacketSize = utils::hostToNetShort(iph->total_len);
    if (packet.size() != expectedPacketSize) {
        return IP::RetCode::EXPECTED_PACKET_SIZE_DOESNT_MATCH_WITH_RECEIVED_PACKET_SIZE;
    }
    return IP::RetCode::OK;
}

IP::RetCode IP::validateHeaderChecksum(Buffer packet) {
    IP_Header *iph = (IP_Header *) packet.data();
    uint16_t checksum = utils::checksum((uint16_t *) packet.data(), iph->getHeaderLenInBytes(), 0);
    if (checksum != 0) {
        return IP::RetCode::INVALID_HEADER_CHECKSUM;
    }
    return IP::RetCode::OK;
}

uint16_t IP::generate_header_checksum(IP_Header *iph) {
    iph->header_checksum = 0;
    return utils::checksum(iph, sizeof(IP_Header), 0);
}

void IPAddr::convertToString() {
    uint8_t *p = (uint8_t *) &addr;
    snprintf(this->str,
            this->MAX_STR_SIZE, 
            "%i.%i.%i.%i",
            p[3], p[2], p[1], p[0]
            );
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

ostream& operator << (ostream& os, IP::RetCode &ret) {
    if (ret == IP::RetCode::OK) {
        os << "IP::RetCode::OK";
    }
    else if (ret == IP::RetCode:: PACKET_SIZE_GREATER_THAN_NETBUF_SIZE) {
        os << "IP::RetCode:: PACKET_SIZE_GREATER_THAN_NETBUF_SIZE";
    }
    else if (ret == IP::RetCode::PACKET_SIZE_LESS_THAN_MIN_PACKET_SIZE) {
        os << "IP::RetCode::PACKET_SIZE_LESS_THAN_MIN_PACKET_SIZE";
    }
    else if (ret == IP::RetCode:: PACKET_SIZE_GREATER_THAN_MAX_PACKET_SIZE) {
        os << "IP::RetCode:: PACKET_SIZE_GREATER_THAN_MAX_PACKET_SIZE";
    }
    else if (ret == IP::RetCode::INVALID_IP_VERSION) {
        os << "IP::RetCode::INVALID_IP_VERSION";
    }
    else if (ret == IP::RetCode::HEADER_LEN_DIFFERENT_FROM_20_BYTES) {
        os << "IP::RetCode::HEADER_LEN_DIFFERENT_FROM_20_BYTES";
    }
    else if (ret == IP::RetCode::EXPECTED_PACKET_SIZE_DOESNT_MATCH_WITH_RECEIVED_PACKET_SIZE) {
        os << "IP::RetCode::EXPECTED_PACKET_SIZE_DOESNT_MATCH_WITH_RECEIVED_PACKET_SIZE";
    }
    else if (ret == IP::RetCode::INVALID_HEADER_CHECKSUM) {
        os << "IP::RetCode::INVALID_HEADER_CHECKSUM";
    }
    return os;
}
