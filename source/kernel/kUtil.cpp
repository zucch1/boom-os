#include "kUtil.h"

static KernelInfo kern_info;

void (*term_write)(const char *string, size_t length);


KernelInfo * KernelInit(stivale2_struct * stiv_struct){
    stivale2_struct_tag_terminal * term_struct = (stivale2_struct_tag_terminal*)stivale2_get_tag(stiv_struct, STIVALE2_STRUCT_TAG_TERMINAL_ID);
    void * term_write_ptr = (void*)term_struct->term_write;
    term_write = (void(*)(const char*, size_t))term_write_ptr;
    // void (*term_write)(const char *string, size_t length) = (void(*)(const char*, size_t))term_write_ptr;

    stivale2_struct_tag_cmdline * cmd_line = (stivale2_struct_tag_cmdline*)stivale2_get_tag(stiv_struct, STIVALE2_STRUCT_TAG_CMDLINE_ID);
    const char * cmd = (const char*)cmd_line->cmdline;
    // printk(cmd);
    
    InitialisePageFrameAllocator(stiv_struct);
    return &kern_info;
}