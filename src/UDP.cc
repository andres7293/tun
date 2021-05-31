#include "UDP.H"
#include "Utils.H"
#include <iostream>

UDP::RetCode UDP::input(IP_Header *iph, Buffer ip_payload) {
    UDP::RetCode ret;
    ret = this->validatePacketSize(ip_payload);
    if (ret != UDP::RetCode::OK)
        return ret;
    ret = this->validateChecksum(ip_payload);
    if (ret != UDP::RetCode::OK)
        return ret;
    return UDP::RetCode::OK;
}

UDP::RetCode UDP::validatePacketSize(Buffer ip_payload) {
    if (ip_payload.size() < UDP::MIN_PACKET_SIZE) {
        return UDP::RetCode::PACKET_SIZE_LESS_THAN_MIN_PACKET_SIZE;
    }
    UDP_Header* udph = (UDP_Header *) ip_payload.data();
    uint16_t expectedPacketSize = utils::netToHostShort(udph->length);
    if (expectedPacketSize != ip_payload.size()) {
        return UDP::RetCode::EXPECTED_PACKET_SIZE_DOESNT_MATCH_WITH_RECEIVED_PACKET_SIZE;
    }
    return UDP::RetCode::OK;
}

UDP::RetCode UDP::validateChecksum(Buffer ip_payload) {
    UDP_Header* udph = (UDP_Header *) ip_payload.data();
    if (udph->checksum == 0) {
        return UDP::RetCode::OK;
    }
    uint16_t checksum = utils::checksum(ip_payload.data(), ip_payload.size(), 0);
    if (checksum != 0) {
        return UDP::RetCode::INVALID_CHECKSUM;
    }
    return UDP::RetCode::OK;
}
