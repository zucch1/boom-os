#include "kernel.h"
#include <stddef.h>
#include "memory.h"
#include "pmm.h"
#include "util.h"

void (*term_write)(const char *string, size_t length);

void initialise_kernel(stivale2_struct * bootinfo){
    // Use the stivale2-provided terminal
    stivale2_struct_tag_terminal * term = (stivale2_struct_tag_terminal*)stivale2_get_tag(bootinfo, STIVALE2_STRUCT_TAG_TERMINAL_ID);
    void * term_write_ptr = (void*)term->term_write;
    term_write = (void(*)(const char*, size_t))term_write_ptr;
    printk(" Initialising kernel:\n");

    // Initialise the PMM and later the VMM
    init_pmm(bootinfo); 
    printk("    - Physical Memory Manager Initialised!\n");

    printk("[i] Kernel Initialised Successfully!\n");
}


void printk(const char * str){
    term_write(str, strlen(str));
}