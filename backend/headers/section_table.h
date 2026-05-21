#ifndef SECTION_TABLE_H
#define SECTION_TABLE_H

#include "../../general/generalheaders/global.h"
#include <cstddef>
#include <sys/types.h>

#define _LBL_SIZE_ 64
#define _NAME_SIZE_ 16
#define _TEXT_SEC_SIZE_ 16000
#define _DATA_SEC_SIZE_ 8000
#define _MAX_PATCHES_ 256

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
    char name[_LBL_SIZE_];
    uint32_t pos;           
} Label_t;

typedef struct {
    char name[_LBL_SIZE_];
    uint32_t patch_pos;     
    uint32_t target_pos;    
    int resolved;
} Patch_t;

typedef struct {
    Section_t text;
    Section_t data;
    Section_t rodata;
    Label_t labels[_MAX_PATCHES_];
    int label_count;
    Patch_t patches[_MAX_PATCHES_];
    int patch_count;
} Binary_t;

extern Binary_t Binary;

#define TEXT_SEC Binary.text
#define DATA_SEC Binary.data
#define RODATA_SEC Binary.rodata

#define S_DATA_(sec)   sec.s_data
#define S_SIZE_(sec)   sec.s_size
#define S_CAP_(sec)    sec.s_cap

#define BIN_DATA_(sec) sec.bin_data
#define BIN_SIZE_(sec) sec.bin_size
#define BIN_CAP_(sec)  sec.bin_cap

#define S_SPRINT(sec, format, ...) S_SIZE_(sec) += (size_t) snprintf(S_DATA_(sec) + S_SIZE_(sec), S_CAP_(sec) - S_SIZE_(sec), format, ##__VA_ARGS__) 
#define TEXT_(format, ...)         S_SPRINT(TEXT_SEC, format "\n", ##__VA_ARGS__)
#define DATA_(format, ...)         S_SPRINT(DATA_SEC, format "\n", ##__VA_ARGS__)

#endif