#ifndef __ICMPV4_H__
#define __ICMPV4_H__

#include <bits/stdint-uintn.h>
#include <string>

#include "Utils.H"
#include "NetDev.H"
#include "NetBuf.H"
#include "Buffer.H"
#include "Protocol.H"

class Stack;

class ICMPv4Header
{
    public:
        uint8_t type;
        uint8_t code;
        uint16_t checksum;
}__attribute__((packed));

class ICMPv4: public Protocol
{
    public:
        ICMPv4(): stack(nullptr) {}
        virtual ~ICMPv4() {}

        void init(Stack& stack) override;
        int input(Packet& packet) override;
        int output(Packet& packet) override; 
        unsigned int getProtocolSize(unsigned int size) override;

        void echo_reply(Packet& packet);

        static const uint8_t ECHO_REQUEST_TYPE = 0x08;
        static const uint8_t ECHO_REQUEST_CODE = 0x00;

        static const uint8_t ECHO_REPLY_TYPE = 0x00;
        static const uint8_t ECHO_REPLY_CODE = 0x00;
    private:
        void send(Packet& packet);
        int checksum(Packet& packet);

        Stack* stack;

};

#endif
