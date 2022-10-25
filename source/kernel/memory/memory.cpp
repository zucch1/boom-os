#include "memory.h"
#include "pmm.h"    // including memory.h includes pmm.h

static size_t size_in_bytes = 0;
size_t get_memory_size(stivale2_struct * bootinfo){
    if(size_in_bytes) return size_in_bytes;
    auto mmap = reinterpret_cast<stivale2_struct_tag_memmap*>(stivale2_get_tag(bootinfo, STIVALE2_STRUCT_TAG_MEMMAP_ID));
    for(uint8_t i = 0; i < mmap->entries; i++){
        size_in_bytes += mmap->memmap[i].length;         // Foreach entry, add its mem_size
    }
    return size_in_bytes;
}
