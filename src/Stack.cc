#include "Stack.H"
#include <iostream>

void Stack::init()
{
    this->ipv4.init(*this);
}

int Stack::network_receive(Packet& input)
{
    this->ipv4.input(input);
    return 0;
}

int Stack::network_send(Packet& output)
{
    return this->netdev->nwrite(output.data(), output.size());
}
