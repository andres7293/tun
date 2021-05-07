#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "MemoryPool.H"

using MemBlock = uint8_t[512];
using MemPool = MemoryPool<MemBlock, 40>;

#endif
