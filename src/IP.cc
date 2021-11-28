#include "IP.H"
#include "Utils.H"
#include "ICMP.H"
#include <cstdint>

IP::RetCode IP::input(INetBuf& nbuf, uint16_t packetSize) {
    IP::RetCode ret;
    Buffer packet{nbuf.data(), packetSize};
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
    Buffer payload = Buffer::createWithOffset(packet, sizeof(IP_Header));
    if (iph->protocol == ICMPV4_PROTOCOL) {
        ICMP icmp {};
        icmp.input(payload);
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
    this->netdev.nwrite((uint8_t *) packet.data(), packet.size());
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

IPAddr::IPAddr() {
    memset((uint8_t *) this->addr, 0, sizeof(IPAddr::addr));
}

IPAddr::IPAddr(uint32_t addr) {
    memcpy((uint8_t *) this->addr, (uint8_t *) &addr, sizeof(uint32_t));
}

IPAddr::IPAddr(string addr) {
    char addr_str[4];
    int i = 0;
    int ip_index = 0;
    for (const auto car: addr) {
        if (car != '.') {
            addr_str[i++] = car;
        }
        else {
            addr_str[i] = '\0';
            this->addr[ip_index++] = std::stoi(addr_str, nullptr, 10);
            i = 0;
        }
    }
    addr_str[i] = '\0';
    this->addr[ip_index++] = std::stoi(addr_str, nullptr, 10);
}

string IPAddr::toString() {
    char str_addr[16];
    snprintf(str_addr,
            16,
            "%i.%i.%i.%i",
            this->addr[0],
            this->addr[1],
            this->addr[2],
            this->addr[3]
            );
    return string(str_addr);
}

/*
 * Get the address in network byte order
 */
uint32_t IPAddr::getAddress() {
    uint32_t* addr = (uint32_t *) this->addr;
    #if ((__BYTE_ORDER__) == (__ORDER_LITTLE_ENDIAN__))
        return utils::swap_endian_u32(*addr);
    #endif
    return *addr;
}

ostream& operator << (ostream& os, IP_Header &h) {
    os   << "IP_Header{"
         << "version_headerlen=0x" << hex << (int) h.version_headerlen           << dec
         << ",tos=0x"              << hex << (int) h.tos                         << dec
         << ",total_len=0x"        << hex << (int) h.total_len                   << dec
         << ",id=0x"               << hex << (int) h.id                          << dec
         << ",flags_fragoffset=0x" << hex << (int) h.flags_fragoffset            << dec
         << ",ttl=0x"              << hex << (int) h.ttl                         << dec
         << ",protocol=0x"         << hex << (int) h.protocol                    << dec
         << ",header_checksum=0x"  << hex << (int) h.header_checksum             << dec
         << ",src_addr="         << IPAddr(h.src_addr).toString() << dec
         << ",dst_addr="         << IPAddr(h.dst_addr).toString() << dec
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
