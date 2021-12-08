#ifndef __STACK_H__
#define __STACK_H__

#include "NetDev.H"
#include "Packet.H"
#include "Protocol.H"
#include "IPv4.H"
#include "ICMPv4.H"

class Stack
{
    public:
        Stack(NetDev& netdev): netdev(&netdev) {}

        void init();
        int network_receive(Packet& input);
        int network_send(Packet& output);
    private:
        NetDev* netdev;

        IPv4 ipv4;
};

#endif
