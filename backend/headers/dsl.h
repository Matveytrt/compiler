#ifndef DSL_H
#define DSL_H

#include <stdint.h>
#include <stdlib.h>
#include "section_table.h"

//#define DEBUG_EMIT

#ifdef DEBUG_EMIT
#define EMIT_DEBUG_PRINT(sec, byte, name)                                           \
    do {                                                                            \
        printf("  EMIT: %s -> 0x%02X at pos %zu\n", name, (byte), (sec)->bin_size); \
    } while(0)
#else
#define EMIT_DEBUG_PRINT(sec, byte, name) do {} while(0)
#endif

#define EMIT_BYTE(sec, byte)                                                      \
    do {                                                                          \
        if ((sec)->bin_size >= (sec)->bin_cap) {                                  \
            (sec)->bin_cap *= 2;                                                  \
            (sec)->bin_data = (uint8_t*)realloc((sec)->bin_data, (sec)->bin_cap); \
        }                                                                         \
        EMIT_DEBUG_PRINT(sec, byte, "EMIT_BYTE");                                 \
        (sec)->bin_data[(sec)->bin_size++] = (byte);                              \
    } while(0)

#define EMIT_MODRM(sec, mod, reg, rm) \
    EMIT_BYTE(sec, ((mod) << 6) | ((reg) << 3) | (rm))

#define EMIT_DWORD(sec, dword)                 \
    do {                                       \
        uint32_t _dword = (dword);             \
        EMIT_BYTE(sec, _dword & 0xFF);         \
        EMIT_BYTE(sec, (_dword >> 8) & 0xFF);  \
        EMIT_BYTE(sec, (_dword >> 16) & 0xFF); \
        EMIT_BYTE(sec, (_dword >> 24) & 0xFF); \
    } while(0)

#define EMIT_QWORD(sec, qword)                 \
    do {                                       \
        uint64_t _qword = (uint64_t)(qword);   \
        EMIT_BYTE(sec, (_qword >> 0) & 0xFF);  \
        EMIT_BYTE(sec, (_qword >> 8) & 0xFF);  \
        EMIT_BYTE(sec, (_qword >> 16) & 0xFF); \
        EMIT_BYTE(sec, (_qword >> 24) & 0xFF); \
        EMIT_BYTE(sec, (_qword >> 32) & 0xFF); \
        EMIT_BYTE(sec, (_qword >> 40) & 0xFF); \
        EMIT_BYTE(sec, (_qword >> 48) & 0xFF); \
        EMIT_BYTE(sec, (_qword >> 56) & 0xFF); \
    } while(0)

#define EMIT_REX(sec, w, r, x, b)                                         \
    do {                                                                  \
        uint8_t _rex = 0x40 | ((w) << 3) | ((r) << 2) | ((x) << 1) | (b); \
        if (_rex != 0x40) EMIT_BYTE(sec, _rex);                           \
    } while(0)

#endif