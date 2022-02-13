/* LICENSING INFO*/
/* pmm description */
// extern uint64_t _KernelStart;

#include "pmm.h"
#include "bitmap.h"
#include "stivale2.h"
#include "kernel.h"
#include "util.h"

static bitmap pmm_bitmap{};
static bool pmm_init = false;
static uint64_t largest_seg = 0;    // The Memory Segment where the pmm_bitmap is
static size_t largest_seg_size = 0;

static uint64_t FreeMemory = 0;
static uint64_t UsedMemory = 0;
static uint64_t ReservedMemory = 0;

// Locks the page frame containing `address`
bool lock_frame(void * address){
    if(!pmm_init) return false;
    uint64_t index = (uint64_t)address/4096;
    if(pmm_bitmap[index]) return true; 
    pmm_bitmap.set(index, 1);
    FreeMemory -= 0x1000;
    UsedMemory += 0x1000;
    return true;
}
bool lock_frames(void * address, uint64_t n_frames){
    for(int i = 0; i < n_frames; i++){
        if(lock_frame((void*)((uint64_t)address + (i*4096)))) continue;
        else return false;
    }
    return true;
}

// Free the page frame containing `address`
bool free_frame(void * address){
    if(!pmm_init) return false;
    uint64_t index = (uint64_t)address/4096;
    if(!pmm_bitmap[index]) return true; 
    pmm_bitmap.set(index, 0);
    FreeMemory += 0x1000;
    UsedMemory -= 0x1000;
    return true;
}
bool free_frames(void * address, uint64_t n_frames){
    for(int i = 0; i < n_frames; i++){
        if(!free_frame((void*)((uint64_t)address + (i*4096)))) return false;    // return false iff free_frame returned false at any moment
    }
    return true;
}
// Reserve the page frame containing `address`
bool reserve_frame(void * address){
    if(!pmm_init) return false;
    uint64_t index = (uint64_t)address/4096;
    if(!pmm_bitmap[index]) return true; 
    pmm_bitmap.set(index, 0);
    FreeMemory      -= 0x1000;
    ReservedMemory  += 0x1000;
    return true;
}
bool reserve_frames(void * address, uint64_t n_frames){
    for(int i = 0; i < n_frames; i++){
        if(lock_frame((void*)((uint64_t)address + (i*4096)))) continue;
        else return false;
    }
    return true;
}
// Unreserve the page frame containing `address`
bool unreserve_frame(void * address){
    if(!pmm_init) return false;
    uint64_t index = (uint64_t)address/4096;
    if(!pmm_bitmap[index]) return true; 
    pmm_bitmap.set(index, 0);
    FreeMemory      += 0x1000;
    ReservedMemory  -= 0x1000;
    return true;
}
bool unreserve_frames(void * address, uint64_t n_frames){
    for(int i = 0; i < n_frames; i++){
        if(unreserve_frame((void*)((uint64_t)address + (i*4096)))) continue;
        else return false;
    }
    return true;
}

//=---------------------------------------------------------=
void init_pmm(stivale2_struct * bootinfo){
    if(pmm_init) return;
    pmm_init = true;
    auto* mmap = (stivale2_struct_tag_memmap*)stivale2_get_tag(bootinfo, STIVALE2_STRUCT_TAG_MEMMAP_ID);
    for(uint8_t i = 0; i < mmap->entries; i++){
        if(mmap->memmap[i].length > largest_seg_size){
            largest_seg_size = mmap->memmap[i].length;
            largest_seg = mmap->memmap[i].base;
        }
    }
    pmm_bitmap = bitmap((uint8_t*)largest_seg, get_memory_size(bootinfo)/4096 + 1);
    memset(pmm_bitmap.buffer, 0, get_memory_size(bootinfo)/4096/8+1);   // Set the buffer to all 1s (reserve all pages)
    FreeMemory = get_memory_size(bootinfo);
    lock_frames(pmm_bitmap.buffer, pmm_bitmap.n_bytes/0x1000);
    for(uint16_t i = 0; i < mmap->entries; i++){
        if(mmap->memmap[i].type != USABLE){
            reserve_frames((void*)mmap->memmap[i].base, mmap->memmap[i].length/0x1000);
        } 
    }
    
}
//=-----------------------------------------------------------=

// Searches linearly from last requested page;
void * request_frame(){
    for(uint64_t i = 0; i < pmm_bitmap.n_bytes*8; i++){
        uint64_t address = 0;
        if(pmm_bitmap[i] == false){
            address = i*4096;
            lock_frame((void*)address);
            return (void*)address;
        }
    }
    return nullptr;
    // Page Swapping
}


size_t GetUsedMemory(){
    return UsedMemory;
}

size_t GetFreeMemory(){
    return FreeMemory;
}

size_t GetReservedMemory(){
    return ReservedMemory;
}