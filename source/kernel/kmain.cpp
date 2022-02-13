#include "kernel.h"
#include "bitmap.h"
#include "util.h"
#include "memory.h"
#include "pmm.h"

extern "C" void kmain(stivale2_struct * bootinfo){
    initialise_kernel(bootinfo);
    printk("Total Memory: "); printk(to_string(get_memory_size(bootinfo)/1024/1024)); printk("MB\n");
    printk("Free Memory: "); printk(to_string(GetFreeMemory()/1024)); printk("KB\n");
    printk("Used Memory: "); printk(to_string(GetUsedMemory()/1024)); printk("KB\n");
    printk("Reserved Memory: "); printk(to_string(GetReservedMemory()/1024)); printk("KB\n");

    for(uint64_t i = 0; i < 20; i++){
        printk(to_hstring64((uint64_t)request_frame()));
        printk("\n");
    }

    printk("\nKernel Done!");
    asm("hlt");
}