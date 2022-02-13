#include "kernel.h"
#include "bitmap.h"
#include "util.h"
#include "memory.h"

stivale2_tag * stivale2_get_tag(stivale2_struct * stiv_struct, uint64_t id);
extern "C" void kmain(stivale2_struct * bootinfo){
    initialise_kernel(bootinfo);
    printk("Kernel Initialised Successfully\n");
    printk("Memory Size: "); printk(to_string(get_memory_size(bootinfo)/1024)); printk("KB\n");
    printk("\nKernel Done!");
    asm("hlt");
}