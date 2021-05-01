#ifndef __ALLOCATOR_H__
#define __ALLOCATOR_H__

#include <stdint.h>
#include <memory>

template<typename T>
class IAllocator {
    public:
        virtual ~IAllocator() {};
        virtual std::unique_ptr<T> alloc() = 0;
};

template<typename T>
class HeapAllocator: public IAllocator<T> {
    public:
        ~HeapAllocator() {}
        std::unique_ptr<T> alloc() {
            return std::unique_ptr<T>(new T);
        }
};

#endif
