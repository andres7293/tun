#include <cstdint>
#include <iostream>

#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "IP.H"
#include "Utils.H"
#include "TunIf.H"
#include "NetDev.H"
#include "NetBuf.H"

using namespace std;

int main(void) {
    TunIf tunif("tun0");
    if (!tunif.alloc()) {
        cout << "Error opening /dev/tun, errno=" << tunif.getErrno() << endl;
        return -1;
    }
    system("ip link set tun0 up");
    system("ip addr add 10.0.0.1/24 dev tun0");
    NetDev netdev(tunif);
    while (1) {
        NetBuf nbuf(1024);
        ssize_t bytesRead = netdev.read(nbuf.getBuf(), nbuf.getSize());
        IP_Packet packet(nbuf.getBuf(), bytesRead, &nbuf);
        IP::ip_input(netdev, packet);
    }
    tunif.dealloc();
    return 0;
}
