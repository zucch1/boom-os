#include "memory.h"



static size_t TotalMemoryBytes = 0;
// Returns Total RAM Size in Bytes (Usable and non-usable)
size_t MemorySize(stivale2_struct * stiv_struct){
    if(TotalMemoryBytes) return TotalMemoryBytes;
    stivale2_struct_tag_memmap * memmap= (stivale2_struct_tag_memmap*)stivale2_get_tag(stiv_struct, STIVALE2_STRUCT_TAG_MEMMAP_ID);
    uint64_t num = memmap->entries;
    stivale2_mmap_entry entry;
    for(uint64_t i = 0; i < num; i++){
        entry = memmap->memmap[i];
        TotalMemoryBytes += entry.length;
    }
    return TotalMemoryBytes;
}