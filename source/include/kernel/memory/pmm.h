#pragma once
#include <stddef.h>
#include <stdint-gcc.h>
#include "memory.h"
#include "bitmap.h"

void init_pmm(stivale2_struct * bootinfo);  // Better Design: Only Give init_pmm access to the memory map

// Locks the page frame containing `address`
bool lock_frame(void * address);
bool lock_frames(void * address, uint64_t n_frames);

// Free the page frame containing `address`
bool free_frame(void * address);
bool free_frames(void * address, uint64_t n_frames);

void * request_frame();
// void * request_frames(); //Continious frames

// Returns true iff the `address` is in a locked page
bool frame_status(void * address);

size_t GetUsedMemory();
size_t GetFreeMemory();
size_t GetReservedMemory();