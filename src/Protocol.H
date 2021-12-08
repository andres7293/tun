#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#include <stdint.h>

#include "Buffer.H"
#include "Packet.H"

class Stack;

class Protocol {
    public:
        Protocol() {}
        virtual ~Protocol() {}

        virtual void init(Stack& stack) = 0;
        /* input loop */
        virtual int input(Packet& packet) = 0;
        /* output loop */
        virtual int output(Packet& packet) = 0;
        /* get the size of protocol buffer size taking into account the protocol overhead*/
        virtual unsigned int getProtocolSize(unsigned int size) = 0; 
};

#endif
