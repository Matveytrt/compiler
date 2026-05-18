#include "../headers/section_table.h"
#include <stdlib.h>
#include <string.h>

#define INIT_SECTION(section_name) { \
    .bin_data = NULL,                \
    .s_data = NULL,                  \
    .bin_size = 0,                   \
    .s_size = 0,                     \
    .bin_cap = 0,                    \
    .s_cap = 0,                      \
    .name = #section_name            \
}

Binary_t Binary = {
    .text = INIT_SECTION(.text),
    .data = INIT_SECTION(.data),
    .rodata = INIT_SECTION(.rodata),
    .patches = {{0}},
    .patch_count = 0
};