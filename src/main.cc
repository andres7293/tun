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
        cout << "Error opening /dev/tun" << endl;
        return -1;
    }
    NetDev netdev(tunif);
    while (1) {
        NetBuf nbuf(1024);
        ssize_t bytesRead = netdev.read(nbuf.getBuf(), nbuf.getSize());
        IP::ip_input(netdev, nbuf.getBuf(), (uint16_t) bytesRead);
    }
    tunif.dealloc();
    return 0;
}
