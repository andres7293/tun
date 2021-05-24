#include "IP.H"
#include "Utils.H"

IP::RetCode IP::input(INetBuf& nbuf, Buffer packet) {
    if (this->validateInputSize(nbuf, packet.size()) < 0) {
        return IP::RetCode::INVALID_INPUT_SIZE;
    }
    return IP::RetCode::OK;
}

int IP::validateInputSize(INetBuf& nbuf, uint16_t packetSize) {
    if (packetSize > nbuf.size()) {
        return -1;
    }
    if (packetSize < IP::MIN_IP_PACKET_SIZE) {
        return -2;
    }
    if (packetSize > IP::MAX_IP_PACKET_SIZE) {
        return -3;
    }
    return 0;
}

IP::RetCode IP::validateHeader(Buffer packet) {
    IP_Header *iph = (IP_Header *) packet.data();
    if (iph->getVersion() != IP::IPV4_VERSION) {
        return IP::RetCode::INVALID_IP_VERSION;
    }
    if (iph->getHeaderLenInBytes() != IP::MIN_IP_PACKET_SIZE) {
        return IP::RetCode::HEADER_LEN_DIFFERENT_FROM_20_BYTES;
    }
    uint16_t expectedPacketSize = iph->total_len;
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
