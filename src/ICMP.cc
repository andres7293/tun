#include "ICMP.H"

int ICMP::icmp_input(NetDev &netdev, IP_Packet &packet) {
    ICMP_Header_t *icmph = (ICMP_Header_t *) packet.get();

    //ping request
    if (icmph->type == 0x08 && icmph->code == 0) {
    }
    return 0;
}

int ICMP::icmp_echo_request(NetDev &netdev, IP_Packet &packet) {
    ICMP_EchoRequest_t *icmph = (ICMP_EchoRequest_t *) packet.get();
    cout << *icmph << endl;
    return 0;
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
