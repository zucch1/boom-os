#include "kUtil.h"

static KernelInfo kern_info;

KernelInfo * KernelInit(stivale2_struct * stiv_struct){
    stivale2_struct_tag_terminal * term_struct = (stivale2_struct_tag_terminal*)stivale2_get_tag(stiv_struct, STIVALE2_STRUCT_TAG_TERMINAL_ID);
    void * term_write_ptr = (void*)term_struct->term_write;
    void (*term_write)(const char *string, size_t length) = (void(*)(const char*, size_t))term_write_ptr;

    return &kern_info;
}