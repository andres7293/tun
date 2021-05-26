#include "ICMP.H"
#include "Utils.H"
#include <iostream>
using namespace std;

ICMP::RetCode ICMP::input(Buffer ip_payload) {
    ICMP::RetCode ret;
    ret = this->validateHeaderSize(ip_payload);
    if (ret != ICMP::RetCode::OK)
        return ret;
    ret = this->validateHeaderChecksum(ip_payload);
    if (ret != ICMP::RetCode::OK)
        return ret;
    ICMP_Header *icmph = (ICMP_Header *) ip_payload.data();
    switch (icmph->type) {
        case ICMP::ECHO_REQUEST_TYPE:
            ret = this->echo_request(icmph, ip_payload);
            break;
        default:
                ret = ICMP::RetCode::UNKNOW;
            break;
    }
    return ret;
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

ICMP::RetCode ICMP::echo_request(ICMP_Header *icmph, Buffer ip_payload) {
    if (icmph->code != ICMP::ECHO_REQUEST_CODE) {
        return ICMP::RetCode::MALFORMED_ICMP_ECHO_REQUEST;
    }
    this->echo_reply(icmph, ip_payload);
    return ICMP::RetCode::ECHO_REPLY;
}

void ICMP::echo_reply(ICMP_Header *icmp, Buffer ip_payload) {
    icmp->type = ICMP::ECHO_REPLY_TYPE;
    icmp->code = ICMP::ECHO_REPLY_CODE;
    icmp->checksum = utils::checksum(ip_payload.data(), ip_payload.size(), 0);
}
