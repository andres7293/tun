#include "ICMP.H"

int ICMP::icmp_input(NetDev &netdev, IP_Header *iph, uint8_t *ip_payload, uint16_t ip_payload_size) {
    ICMP_Header_t *icmph = (ICMP_Header_t *) ip_payload;

    //ping request
    if (icmph->type == 0x08 && icmph->code == 0) {
    }
    return 0;
}
