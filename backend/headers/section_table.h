#ifndef SECTION_TABLE_H
#define SECTION_TABLE_H

#include "../../general/generalheaders/global.h"
#include <cstddef>
#include <sys/types.h>

#define _NAME_SIZE_ 16
#define _TEXT_SEC_SIZE_ 16000
#define _DATA_SEC_SIZE_ 8000

typedef struct 
{
    uint8_t *bin_data;
    char    *s_data;
    size_t   bin_size;
    size_t   s_size;
    size_t   bin_cap;
    size_t   s_cap;
    char     name[_NAME_SIZE_];
} Section_t;

typedef struct {
    Section_t text;
    Section_t data;
    Section_t rodata;
} Binary_t;

extern Binary_t Binary;

#endif