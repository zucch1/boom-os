#pragma once
#include "stivale2.h"
#include <stddef.h>
#include "printk.h"
#include "pfalloc.h"
struct KernelInfo{

};

void * stivale2_get_tag(stivale2_struct * stiv_struct, uint64_t id);
KernelInfo * KernelInit(stivale2_struct * stivale2_struct);
