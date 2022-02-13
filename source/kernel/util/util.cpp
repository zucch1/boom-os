#include "util.h"

char ToStrBuf[128];
const char * to_string(int64_t value){
    uint8_t isNeg = 0;
    if(value<0){
        isNeg = 1;
        value *= -1;
        ToStrBuf[0] = '-';
    }
    uint8_t size = 0;
    uint64_t sizeTest = value;
    while(sizeTest/10 > 0){
        sizeTest /= 10;
        size++;
    }
    uint8_t index = 0;
    while(value / 10 > 0){
        uint8_t rem = value%10;
        value /= 10;
        ToStrBuf[isNeg + size - index] = rem + '0';
        index++;
    }
    uint8_t rem = value%10;
    ToStrBuf[isNeg + size - index] = rem + '0';
    ToStrBuf[isNeg + size + 1] = 0;
    return ToStrBuf;
}

// TODO: Refactor all to_hstrings to remove compiler warnings
// Fir the `8th iteration` problem (undefined behaviour while indexing -1)
char HexToStrBuf64[64];
const char * to_hstring64(uint64_t value){
    uint64_t * valPtr = &value;
    uint8_t * ptr;
    uint8_t temp;
    uint8_t size = 8*2 - 1;
    for(uint8_t i = 0; i < size; i++){
        ptr = ((uint8_t*)valPtr + i);
        temp = ((*ptr & 0xf0) >> 4);
        HexToStrBuf64[size - (i*2 + 1)] = temp + (temp>9 ? 55:'0');
        temp = (*ptr & 0x0f);
        HexToStrBuf64[size - (i*2)] = temp + (temp>9 ? 55:'0');

    }
    HexToStrBuf64[size + 1] = 0;
    return HexToStrBuf64;
}

char HexToStrBuf32[64];
const char * to_hstring32(uint32_t value){
    uint32_t * valPtr = &value;
    uint8_t * ptr;
    uint8_t temp;
    uint8_t size = 4*2 - 1;
    for(uint8_t i = 0; i < size; i++){
        ptr = ((uint8_t*)valPtr + i);
        temp = ((*ptr & 0xf0) >> 4);
        HexToStrBuf32[size - (i*2 + 1)] = temp + (temp>9 ? 55:'0');
        temp = (*ptr & 0x0f);
        HexToStrBuf32[size - (i*2)] = temp + (temp>9 ? 55:'0');

    }
    HexToStrBuf32[size + 1] = 0;
    return HexToStrBuf32;
}

char HexToStrBuf16[64];
const char * to_hstring16(uint16_t value){
    uint16_t * valPtr = &value;
    uint8_t * ptr;
    uint8_t temp;
    uint8_t size = 2*2 - 1;
    for(uint8_t i = 0; i < size; i++){
        ptr = ((uint8_t*)valPtr + i);
        temp = ((*ptr & 0xf0) >> 4);
        HexToStrBuf16[size - (i*2 + 1)] = temp + (temp>9 ? 55:'0');
        temp = (*ptr & 0x0f);
        HexToStrBuf16[size - (i*2)] = temp + (temp>9 ? 55:'0');

    }
    HexToStrBuf16[size + 1] = 0;
    return HexToStrBuf16;
}

char HexToStrBuf8[64];
const char * to_hstring8(uint8_t value){
    uint8_t * valPtr = &value;
    uint8_t * ptr;
    uint8_t temp;
    uint8_t size = 1*2 - 1;
    for(uint8_t i = 0; i < size; i++){
        ptr = ((uint8_t*)valPtr + i);
        temp = ((*ptr & 0xf0) >> 4);
        HexToStrBuf8[size - (i*2 + 1)] = temp + (temp > 9 ? 55 : '0');
        temp = (*ptr & 0x0f);
        HexToStrBuf8[size - (i*2)] = temp + (temp > 9 ? 55 : '0');

    }
    HexToStrBuf8[size + 1] = 0;
    return HexToStrBuf8;
}

// strlen.c
size_t strlen(const char * str){
    size_t size = 0;
    while(str[size]) size++;
    return size;
}




        //***********************************************************//
        //------------- The Standard C Library: stdlib.h-------------//
        //***********************************************************//
// memmove.c
void * memmov(void* dstptr, const void* srcptr, size_t size){
    unsigned char * dst = (unsigned char*)dstptr;
    const unsigned char* src = (const unsigned char*)srcptr;
    if(dst < src){
        for(size_t i = 0; i < size; i++) dst[i] = src[i];
    } else {
        for(size_t i = size; i != 0; i--) dst[i-1] = src[i-1];
    }
    return dstptr;
}

// memset.c
void * memset(void* bufptr, int value, size_t size){
    unsigned char* buf = (unsigned char*) bufptr;
    for(size_t i = 0; i < size; i++){
        buf[i] = (unsigned char)value;
    }
    return bufptr;
}

// memcpy.c
void * memcpy(void* __restrict dstptr, const void* __restrict srcptr, size_t size){
    unsigned char* dst = (unsigned char*)dstptr;
    const unsigned char* src = (const unsigned char*)srcptr;
    for(size_t i = 0; i < size; i++) dst[i] = src[i];
    return dstptr;
}

// memcmp.c
int memcmp(const void* aptr, const void* bptr, size_t size){
    const unsigned char* a = (const unsigned char*)aptr;
    const unsigned char* b = (const unsigned char*)bptr;
    for(size_t i = 0; i < size; i++){
        if(a[i] < b[i]) return -1;
        else if(b[i] < a[i]) return 1;
    }
    return 0;
}