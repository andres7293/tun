#ifndef __TUNIF_H__
#define __TUNIF_H__

#include <stdint.h>
#include <sys/types.h>

int tun_alloc(char *dev);
ssize_t tun_read(int fd, uint8_t *buf, size_t len);
ssize_t tun_write(int fd, uint8_t *buf, size_t len);

#endif
