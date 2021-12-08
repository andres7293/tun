#include "IPv4.H"
#include "Utils.H"
#include "Stack.H"
#include <cstdint>

void IPv4::init(Stack& stack)
{
    this->stack = &stack;
    this->icmp4.init(stack);
}

int IPv4::input(Packet& packet)
{
    if (packet.size() < IPv4Header::MIN_HEADER_SIZE_BYTES) {
        return -1;
    }
    else if (packet.size() > IPv4Header::MAX_PACKET_SIZE) {
        return -2;
    }
    IPv4Header *iph = (IPv4Header *) packet.data();
    if (iph->getVersion() != IPv4Header::IPV4_VERSION) {
        return -3;
    }
    if (iph->getHeaderLenInBytes() != IPv4Header::MIN_PACKET_SIZE) {
        return -4;
    }
    
    uint16_t expectedPacketSize = utils::hostToNetShort(iph->total_len);
    if (packet.size() != expectedPacketSize) {
        return -5;
    }

    if (this->checksum(iph) != 0) {
        return -6;
    }

    packet.setNetworkLayer(packet.data(), iph->getHeaderLenInBytes());

    packet.setTransportLayer(
            packet.data() + iph->getHeaderLenInBytes(),
            packet.size() - iph->getHeaderLenInBytes()
            );

    if (iph->protocol == ICMPV4_PROTOCOL) {
        icmp4.input(packet);
    }
    if (iph->protocol == UDPV4_PROTOCOL) {
    }
    return 0;
}

int IPv4::output(Packet& packet)
{
    return 0;
}

unsigned int IPv4::getProtocolSize(unsigned int size)
{
    return size + sizeof(IPv4Header);
}

int IPv4::checksum(IPv4Header* header)
{
    return utils::checksum((uint16_t *) header,
            header->getHeaderLenInBytes(),
            0);
}

uint8_t IPv4Header::getVersion()
{
    return ((this->version_headerlen & 0xf0) >> 4);
}

uint8_t IPv4Header::getHeaderLen()
{
    return (this->version_headerlen & 0x0f);
}

uint8_t IPv4Header::getHeaderLenInBytes()
{
    return this->getHeaderLen() * 4;
}

uint8_t IPv4Header::getFlags()
{
    return ((this->flags_fragoffset & 0xE000) >> 13);
}

uint8_t IPv4Header::getFragmentOffset()
{
    return (this->flags_fragoffset & 0x1FFF);
}

IPv4Addr::IPv4Addr()
{
    memset((uint8_t *) this->addr, 0, sizeof(IPv4Addr::addr));
}

IPv4Addr::IPv4Addr(uint32_t addr) {
    memcpy((uint8_t *) this->addr, (uint8_t *) &addr, sizeof(uint32_t));
}

IPv4Addr::IPv4Addr(std::string addr)
{
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

std::string IPv4Addr::toString()
{
    char str_addr[16];
    snprintf(str_addr,
            16,
            "%i.%i.%i.%i",
            this->addr[0],
            this->addr[1],
            this->addr[2],
            this->addr[3]
            );
    return std::string(str_addr);
}

/*
 * Get the address in network byte order
 */
uint32_t IPv4Addr::getAddress()
{
    uint32_t* addr = (uint32_t *) this->addr;
    #if ((__BYTE_ORDER__) == (__ORDER_LITTLE_ENDIAN__))
        return utils::swap_endian_u32(*addr);
    #endif
    return *addr;
}

