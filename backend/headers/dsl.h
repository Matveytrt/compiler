#ifndef DSL_H
#define DSL_H

#include <stdint.h>
#include <stdlib.h>
#include "section_table.h"

#define EMIT_BYTE(sec, byte) \
    do { \
        if ((sec)->bin_size >= (sec)->bin_cap) { \
            (sec)->bin_cap *= 2; \
            (sec)->bin_data = (uint8_t*)realloc((sec)->bin_data, (sec)->bin_cap); \
        } \
        (sec)->bin_data[(sec)->bin_size++] = (byte); \
    } while(0)

#define EMIT_WORD(sec, word) \
    do { \
        EMIT_BYTE(sec, (word) & 0xFF); \
        EMIT_BYTE(sec, ((word) >> 8) & 0xFF); \
    } while(0)

#define EMIT_DWORD(sec, dword) \
    do { \
        EMIT_BYTE(sec, (dword) & 0xFF); \
        EMIT_BYTE(sec, ((dword) >> 8) & 0xFF); \
        EMIT_BYTE(sec, ((dword) >> 16) & 0xFF); \
        EMIT_BYTE(sec, ((dword) >> 24) & 0xFF); \
    } while(0)

#define EMIT_QWORD(sec, qword) \
    do { \
        EMIT_DWORD(sec, (qword) & 0xFFFFFFFF); \
        EMIT_DWORD(sec, ((qword) >> 32) & 0xFFFFFFFF); \
    } while(0)

#define EMIT_REX(sec, w, r, x, b) \
    do { \
        uint8_t _rex = 0x40 | ((w) << 3) | ((r) << 2) | ((x) << 1) | (b); \
        if (_rex != 0x40) EMIT_BYTE(sec, _rex); \
    } while(0)

#define EMIT_MODRM(sec, mod, reg, rm) \
    EMIT_BYTE(sec, ((mod) << 6) | ((reg) << 3) | (rm))

#endif