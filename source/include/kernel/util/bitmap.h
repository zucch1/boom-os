#pragma once
#include <stdint-gcc.h>

// An array of bits(not bools)
class bitmap{
public:
    uint8_t * buffer;
    uint32_t n_bytes;
    void set(uint64_t index, bool status);
    bool operator[](uint64_t index);
    bitmap();
    bitmap(uint8_t * buffer, uint32_t n_items);
};

//TODO:   Create a `find_first(bool)` algorithm implementation
//   to find the first element that is either set or unset
//