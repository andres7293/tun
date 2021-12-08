#include <cstdint>
#include <iostream>
#include <memory>

#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "Utils.H"
#include "TunIf.H"
#include "NetDev.H"
#include "NetBuf.H"
#include "Packet.H"
#include "Stack.H"

using namespace std;

int main(void) {
    TunIf tunif{"tun0"};
    NetDev netdev{tunif};
    Stack stack { netdev };
    stack.init();
    if (!tunif.alloc()) {
        cout << "Error opening /dev/tun, errno=" << tunif.getErrno() << endl;
        return -1;
    }
    system("ip link set tun0 up");
    system("ip addr add 10.0.0.1/24 dev tun0");
    NetBuf nbuf(1024);
    while (1) {
        unsigned int bytesRead = netdev.nread(nbuf.data(), nbuf.size());
        Packet packet {nbuf.data(), bytesRead};
        stack.network_receive(packet);
    }
    tunif.dealloc();
    return 0;
}
