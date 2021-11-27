#include <cstdint>
#include <iostream>
#include <memory>

#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "IP.H"
#include "Utils.H"
#include "TunIf.H"
#include "NetDev.H"
#include "NetBuf.H"
#include "Packet.H"

using namespace std;

int main(void) {
    TunIf tunif{"tun0"};
    if (!tunif.alloc()) {
        cout << "Error opening /dev/tun, errno=" << tunif.getErrno() << endl;
        return -1;
    }
    NetDev netdev{tunif};
    IP ip{netdev};
    system("ip link set tun0 up");
    system("ip addr add 10.0.0.1/24 dev tun0");
    NetBuf nbuf(1024);
    while (1) {
        size_t bytesRead = netdev.nread(nbuf.data(), nbuf.size());
        ip.input(nbuf, bytesRead);
    }
    tunif.dealloc();
    return 0;
}
