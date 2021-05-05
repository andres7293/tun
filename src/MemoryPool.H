#ifndef __MEMORYPOOL_H__
#define __MEMORYPOOL_H__

#include <bits/stdint-uintn.h>
#include <stdint.h>

template <int BLOCKSIZE>
class MemoryBlock {
    public:
        uint8_t* getBuf() {
            return this->block;
        }
        int getSize() {
            return sizeof(uint8_t) * BLOCKSIZE;
        }
    private:
        uint8_t block[BLOCKSIZE];
};

template <int BLOCKSIZE, int NUMBLOCKS>
class MemoryPool {
    public:
        MemoryPool() {
            for (unsigned int i = 0; i < NUMBLOCKS; i++)
                this->freeList[i] = 0;
        }
        MemoryBlock<BLOCKSIZE>* alloc() {
            for (unsigned int i = 0; i < NUMBLOCKS; i++) {
                if (this->freeList[i] == 0) {
                    this->freeList[i] = 1;
                    return &this->pool[i];
                }
            }
            return nullptr;
        }
        int free(MemoryBlock<BLOCKSIZE>* block) {
            if (block == nullptr)
                return -1;
            for (unsigned int i = 0; i < NUMBLOCKS; i++) {
                if (block == &this->pool[i]) {
                    this->freeList[i] = 0;
                    return 0;
                }
            }
            return -2;
        }
        int getNumBlocks() {
            return NUMBLOCKS;
        }
        int getTotalSize() {
            return this->pool[0].getTotalSize * NUMBLOCKS;
        }
        int getBlockSize() {
            return BLOCKSIZE;
        }
    private:
        MemoryBlock<BLOCKSIZE> pool[NUMBLOCKS];
        unsigned int freeList[NUMBLOCKS];
};

#endif
