#pragma once
#include "stivale2.h"
#include <stddef.h>
#include "memory.h"

class BITMAP {
    size_t size;    // Size of the buffer
    char * buffer;  // Pointer to start of the buffer
public:
    BITMAP(size_t size, char * buffer);
    bool operator[](uint64_t index); // index refers to the address/4096 a.k.a the pageIndex
    void set(uint64_t index, bool status);
    size_t getsize(){return size;}
};

// TODO:
bool InitialisePageFrameAllocator(stivale2_struct * stiv_struct); // static
void * RequestPage();
void * RequestPages(uint32_t num);
void * RequestcPages(uint32_t num);
bool AllocPages(uint32_t num);
bool FreePage();
bool FreePages(uint32_t num);