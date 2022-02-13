#pragma once
#include <stddef.h>
#include <stdint-gcc.h>

// Will rationalise this:
const char * to_string(int64_t value);
// const char * to_hstring(uint64_t value);
const char * to_hstring8(uint8_t value);
const char * to_hstring16(uint16_t value);
const char * to_hstring32(uint32_t value);
const char * to_hstring64(uint64_t value);
    // Will become part of libc or/and libk


#ifdef __cplusplus
extern "C" {
#endif

size_t strlen(const char * str);
int memcmp(const void*, const void*, size_t);
void * memcpy(void* __restrict, const void* __restrict, size_t);
void * memmov(void*, const void*, size_t);
void * memset(void*, int, size_t);

#ifdef __cplusplus
}
#endif