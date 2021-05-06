#ifndef __MEMORYPOOL_H__
#define __MEMORYPOOL_H__

#include <bits/stdint-uintn.h>
#include <stdint.h>

template <typename T, int NUMBLOCKS>
class MemoryPool {
    public:
        MemoryPool() {
            this->numBlocksFree = NUMBLOCKS;
            for (unsigned int i = 0; i < NUMBLOCKS; i++)
                this->freeList[i] = 0;
        }
        T* alloc() {
            for (unsigned int i = 0; i < NUMBLOCKS; i++) {
                if (this->freeList[i] == 0) {
                    this->freeList[i] = 1;
                    this->numBlocksFree--;
                    return &this->pool[i];
                }
            }
            return nullptr;
        }
        int free(T* block) {
            if (block == nullptr)
                return -1;
            for (unsigned int i = 0; i < NUMBLOCKS; i++) {
                if (block == &this->pool[i]) {
                    if (this->freeList[i] == 0) {
                        return -2;
                    }
                    this->freeList[i] = 0;
                    this->numBlocksFree++;
                    return 0;
                }
            }
            return -3;
        }
        int getNumBlocks() {
            return NUMBLOCKS;
        }
        int getTotalSize() {
            return sizeof(T) * NUMBLOCKS;
        }
        int getBlockSize() {
            return sizeof(T);
        }
        int getNumBlocksFree() {
            return this->numBlocksFree;
        }
    private:
        T pool[NUMBLOCKS];
        unsigned int freeList[NUMBLOCKS];
        int numBlocksFree;
};

template <typename T, int NUMBLOCKS>
ostream& operator << (ostream& os, MemoryPool<T, NUMBLOCKS> &p) {
    cout << "MemoryPool{"
        << "numBlocks=" 
        << p.getNumBlocks()
        << ",blockSize=" << p.getBlockSize()
        << ",totalSize=" << p.getTotalSize()
        << ",numBlocksFree=" << p.getNumBlocksFree()
        << "}";
    return os;
}

#endif
