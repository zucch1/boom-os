#include "bitmap.h"

void bitmap::set(uint64_t index, bool status){
    uint32_t byteIndex = index/8;
    uint32_t bitIndex = 0b00000001 << (index % 8);
    buffer[byteIndex] &= ~bitIndex;
    if(status){
        buffer[byteIndex] |= bitIndex;
    }
}

bool bitmap::operator[](uint64_t index){
    uint32_t byteIndex = index/8;
    uint32_t bitIndex = 0b00000001 << (index % 8);
    return (buffer[byteIndex] & bitIndex);
}

    bitmap::bitmap(){
        return;
    }
    bitmap::bitmap(uint8_t * buffer, uint32_t n_items){
        this->buffer = buffer;
        this->n_bytes = n_items/8;
    }