#pragma once
#include "stivale2.h"

// printk - stub for actual printk
void printk(const char * str);
void initialise_kernel(stivale2_struct * bootinfo);