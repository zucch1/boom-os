#include "stivale2.h"
#include <stddef.h>

//********************************************//
//---------------Stivale2 Specs---------------//
//********************************************//

static uint8_t stack[16384];

static stivale2_header_tag_terminal term_hdr = {
    .tag = {
        .identifier = STIVALE2_HEADER_TAG_TERMINAL_ID,
        .next = static_cast<uint64_t>(NULL)
    },
    .flags = 0,
    .callback = static_cast<uint64_t>(NULL)
};

__attribute__ ((section(".stivale2hdr"), used)) static stivale2_header stiv_hdr = {
    .entry_point = 0,
    .stack = reinterpret_cast<uint64_t>(stack),
    .flags = (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4),
    .tags = reinterpret_cast<uint64_t>(&term_hdr)
};


//*****************************************//
//------------Helper Functions-------------//
//*****************************************//

stivale2_tag * stivale2_get_tag(stivale2_struct * stiv_struct, uint64_t id){
    stivale2_tag * curr_tag = (stivale2_tag*)stiv_struct->tags;
    while(curr_tag != nullptr){
        if(curr_tag->identifier == id) return curr_tag;
        curr_tag = reinterpret_cast<stivale2_tag*>(curr_tag->next);
    }
    return curr_tag;
}