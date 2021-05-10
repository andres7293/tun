#include "ICMP.H"

int ICMP::icmp_input(NetDev &netdev, IP_Packet &packet) {
    ICMP_Header_t *icmph = (ICMP_Header_t *) IP::getPayload(packet).get();
    //ping request
    if (icmph->type == 0x08 && icmph->code == 0) {
        ICMP::icmp_echo_request(netdev, packet);
    }
    return 0;
}

int ICMP::icmp_echo_request(NetDev &netdev, IP_Packet &packet) {
    IP_Payload payload = IP::getPayload(packet);
    ICMP_EchoRequest_t *icmph = (ICMP_EchoRequest_t *) payload.get();
    if (ICMP::validate_icmp_header_checksum(payload) != 0) {
        return -1;
    }
    //create echo reply reutilizing same input packet
    icmph->type = 0x00;
    icmph->code = 0;
    //calculate icmp checksum, skip checksum field
    icmph->checksum = ICMP::icmp_header_checksum(payload);
    IP::ip_output(netdev, packet);
    return 0;
}

uint16_t ICMP::icmp_header_checksum(IP_Payload &payload) {
    ICMP_Header_t *h = (ICMP_Header_t *) payload.get();
    //calculate icmp checksum, skip checksum field
    h->checksum = 0;
    return utils::checksum((void *) h, payload.getSize(), 0);
}

uint16_t ICMP::validate_icmp_header_checksum(IP_Payload &payload) {
    ICMP_Header_t *h = (ICMP_Header_t *) payload.get();
    return utils::checksum((void *) h, payload.getSize(), 0);
}

ostream& operator << (ostream& os, ICMP_EchoRequest_t &h) {
    os << "ICMP_EchoRequest_t{"
        << "type=0x" << hex << (int) h.type << dec
        << ",code=0x" << hex << (int) h.code << dec
        << ",checksum=0x" << hex << (int) h.checksum << dec
        << ",identifier=0x" << hex << (int) h.identifier << dec
        << ",seq_number=0x" << hex << (int) h.seq_number << dec
        << "}";
    return os;
}
