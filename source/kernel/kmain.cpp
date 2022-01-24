#include "stivale2.h"
#include "kUtil.h"
#include "pfalloc.h"

extern "C" void kmain(stivale2_struct * stiv_struct){

    KernelInfo * kern_info = KernelInit(stiv_struct);


    asm("hlt");
}