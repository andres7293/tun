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

using namespace std;

uint8_t buf[1024 * 1];

void print_header_host(IP_Header_t *h);

int main(void) {
    TunIf tunif("tun0");
    if (!tunif.alloc()) {
        cout << "Error opening /dev/tun" << endl;
        return -1;
    }
    NetDev netdev(tunif);
    while (1) {
        ssize_t bytesRead = netdev.read(buf, sizeof(buf));
        IP::ip_input(netdev, buf, (uint16_t) bytesRead);
    }
    tunif.dealloc();
    return 0;
}
