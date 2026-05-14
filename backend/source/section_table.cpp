#include "../headers/section_table.h"

#define INIT_SECTION(section_name) section_name = {NULL, NULL, 0, 0, 0, 0, #section_name}

Binary_t Binary = {
                        INIT_SECTION(.text),
                        INIT_SECTION(.data), 
                        INIT_SECTION(.rodata),                         
};