#include "pfalloc.h"
#include "printk.h"

// TODO: Fix BITMAP indexing logic

// This class is only in the pageframeallocator
// class BITMAP {
//     size_t size;
//     char * buffer;
// public:
//     BITMAP(size_t size /* Size in Bytes*/);
//     BITMAP(size_t size /* Size in Bytes*/, char * buffer);
//     bool operator[](uint64_t pageAddress);
//     void set(uint64_t pageAddress, bool status);
//     size_t getsize(){return size;}
// };


static BITMAP PageFrameBitmap = BITMAP(0, 0);
static void * LargestMemSeg = nullptr;      // ptr to the largest memseg
static uint64_t LargestMemSegSize = 0;      // Size in Bytes

static bool BitmapInit = false;
static bool pfaInit = false;


BITMAP::BITMAP(size_t size /* Size in Bytes*/, char * buffer){
    this->size = size;
    this->buffer = buffer;
}
// Note: All Addresses shall be page aligned (0xABCD...1000 i.e end with 1000)
bool BITMAP::operator[](uint64_t index){
    uint64_t byteIndex = index/8;
    uint8_t bitIndex = byteIndex % 8;
    uint8_t bitIndexer = 0b10000000 >> bitIndex;
    if((buffer[byteIndex] & bitIndexer) > 0){
        return true;
    }
    return false;
}
void BITMAP::set(uint64_t index, bool status){
    uint64_t byteIndex = index/8;
    uint8_t bitIndex = byteIndex % 8;
    uint8_t bitIndexer = 0b10000000 >> bitIndex;
    buffer[byteIndex] &= ~bitIndexer;
    if(status){
        buffer[byteIndex] |= bitIndexer;
    }
}


/*  true -> Page was Locked already or just now
*   false -> 1) PageFrameAllocator not Initialised
*            2) Invalid Address
*/ 
bool LockPage(void * pageAddress){
    if(!pfaInit) return false;

    if(((uint64_t)pageAddress) < PageFrameBitmap.getsize()){
        PageFrameBitmap.set((uint64_t)pageAddress, true);
        return true;
    }
    return false;
}

static bool InitialiseBitmap(stivale2_struct * stiv_struct, uint64_t Size){
    if(BitmapInit) return true;
    stivale2_struct_tag_memmap * mmap = (stivale2_struct_tag_memmap*)stivale2_get_tag(stiv_struct, STIVALE2_STRUCT_TAG_MEMMAP_ID);
    stivale2_mmap_entry entry;
    for(uint64_t i = 0; i < mmap->entries; i++){
        entry = mmap->memmap[i];
        if(entry.length > LargestMemSegSize && entry.type == STIVALE2_MMAP_USABLE){
            LargestMemSegSize = entry.length;
            LargestMemSeg = (void*)entry.base;
        }
    }
    *(bool*)LargestMemSeg = {0};
    PageFrameBitmap = BITMAP(Size, (char*)LargestMemSeg);
    uint64_t memSize = GetMemorySize(stiv_struct);
    for(uint64_t i = 0; i < memSize; i += 4096){
        PageFrameBitmap.set(i, 0);
    }
    BitmapInit = true;
    return BitmapInit;
}

// pfaInit = false; // lvl1 Optimization ;-) [Cache the first initialisation]
bool InitialisePageFrameAllocator(stivale2_struct * stiv_struct){
    if(pfaInit) return true; // lvl1 Optimization cont...
    uint64_t TotalMemoryBytes = GetMemorySize(stiv_struct);
    InitialiseBitmap(stiv_struct, TotalMemoryBytes);
    LockPage(LargestMemSeg);
    LockPage(LargestMemSeg + 1);
    printk("Page Frame Allocator Initialised! \n");
    printk(to_string((int64_t)PageFrameBitmap[(uint64_t)LargestMemSeg]));
    pfaInit = true;
    return true;
}

/*  TODO: Stack[and LinkedList] Approach (See https://wiki.osdev.org/Page_Frame_Allocation)
*   The Address of free page frames are stored in a stack.
*   Allocating a page entails popping the address from the stack [O(1)]
*   Freeing a pageframe is also O(1) and entails adding the address to the stack
*   Checking a pageframe status can be done with addess-sorted metadata about each pageframe
*   TOTHINK: efficient DMA and contigious allocations using Stack/LinkedList approach
*/
