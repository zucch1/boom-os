#pragma once
#include "stivale2.h"
#include <stddef.h>
#define PAGE_SIZE           0x1000
#define page_align(a)       ((a)-((a)%(PAGE_SIZE)))

// Returns the Total Memory Size in `number of bytes`
size_t get_memory_size(stivale2_struct * bootinfo);
