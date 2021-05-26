#include "ICMP.H"
#include "Utils.H"

ICMP::RetCode ICMP::input(Buffer ip_payload) {
    ICMP::RetCode ret;
    ret = this->validateHeaderSize(ip_payload);
    if (ret != ICMP::RetCode::OK)
        return ret;
    ret = this->validateHeaderChecksum(ip_payload);
    if (ret != ICMP::RetCode::OK)
        return ret;
    return ICMP::RetCode::OK;
}

ICMP::RetCode ICMP::validateHeaderSize(Buffer ip_payload) {
    if (ip_payload.size() < sizeof(ICMP_Header)) {
        return ICMP::RetCode::HEADER_SIZE_TOO_SHORT;
    }
    return ICMP::RetCode::OK;
}

ICMP::RetCode ICMP::validateHeaderChecksum(Buffer ip_payload) {
    uint16_t checksum = utils::checksum(ip_payload.data(), ip_payload.size(), 0);
    if (checksum == 0) {
        return ICMP::RetCode::OK;
    }
    return ICMP::RetCode::CHECKSUM_ERROR;
}
