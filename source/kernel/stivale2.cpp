#include "stivale2.h"
#include <stddef.h>

static uint8_t stack[8192];

static stivale2_header_tag_terminal term_hdr = {
    .tag = {
        .identifier = STIVALE2_HEADER_TAG_TERMINAL_ID,
        .next = NULL
    }
};

__attribute__ ((section(".stivale2hdr"), used)) static stivale2_header stiv_hdr = {
    .entry_point = 0,
    .stack = (uint64_t)stack,
    .flags = (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4),
    .tags = (uint64_t)&term_hdr
};

void * stivale2_get_tag(stivale2_struct * stiv_struct, uint64_t id){
    stivale2_tag * curr_tag = (stivale2_tag*)stiv_struct->tags;
    for(;;){
        if(curr_tag == NULL) return NULL;
        if(curr_tag->identifier == id) {
            return curr_tag;
        }
        curr_tag = (stivale2_tag*)curr_tag->next;
    }
}

// stivale2_module * stivale2_get_module_by_name(const char * mod_string, stivale2_struct_tag_modules * mods_tag) {
//     for (uint64_t i = 0; i < mods_tag->module_count; i++){
//         stivale2_module * mod = (stivale2_module*)(uint64_t(mods_tag->modules) + (i * sizeof(stivale2_module)));
//         if(!strcmp(mod_string, mod->string)){
//             return mod;
//         }
//     }
//     return NULL;
// }