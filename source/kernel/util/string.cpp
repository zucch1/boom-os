#include "util/string.h"

char ToStrBuf[32];
char * to_string(int64_t value){
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


char * to_hstring(uint64_t value, uint64_t length = 8){
    
}






// strlen.c
size_t strlen(const char * str){
    size_t size = 0;
    while(str[size]) size++;
    return size;
}

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
    for(size_t i = 0; i < size; i++) dst[i] == src[i];
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