#include "ICMPv4.H"
#include "Stack.H"

void ICMPv4::init(Stack& stack)
{
    this->stack = &stack;
}

int ICMPv4::input(Packet& packet)
{
    int payload_size = packet.getTransportLayer().size();
    if (payload_size < sizeof(ICMPv4Header)) {
        return -1;
    }
    if (this->checksum(packet) != 0) {
        return -2;
    }
    ICMPv4Header *header = (ICMPv4Header *) packet.getTransportLayer().data();

    if (header->type == ICMPv4::ECHO_REQUEST_TYPE) {
        echo_reply(packet);
    }
    return 0;
}

int ICMPv4::output(Packet& packet)
{
    return 0;
}

unsigned int ICMPv4::getProtocolSize(unsigned int size)
{
    return size + sizeof(ICMPv4Header);
}

void ICMPv4::echo_reply(Packet& packet)
{
    ICMPv4Header *icmph = (ICMPv4Header *) packet.getTransportLayer().data();

    //calculate ICMPv4 checksum
    icmph->type = ICMPv4::ECHO_REPLY_TYPE;
    icmph->code = ICMPv4::ECHO_REPLY_CODE;
    icmph->checksum = 0;
    icmph->checksum = this->checksum(packet);

    IPv4Header* iph = (IPv4Header *) packet.getNetworkLayer().data();
    uint32_t src = iph->src_addr;
    uint32_t dst = iph->dst_addr;
    iph->src_addr = dst;
    iph->dst_addr = src;
    iph->header_checksum = 0;
    iph->header_checksum = utils::checksum(
            iph,
            iph->getHeaderLenInBytes(),
            0);

    this->send(packet);
}

/*
*
* The checksum for ICMPv4 is calculated with:
*       ICMPv4 header + payload
*/
int ICMPv4::checksum(Packet& packet)
{
    uint8_t* icmph = (uint8_t *) packet.getTransportLayer().data();
    unsigned int icmp_size = packet.getTransportLayer().size();
    return utils::checksum(icmph, icmp_size, 0);
}

void ICMPv4::send(Packet& packet)
{
    if (this->stack != nullptr) {
        this->stack->network_send(packet);
    }
}
