#ifndef REVERSE_H
#define REVERSE_H

#include "../../../general/source/generalheaders/treefuncs.h"
#include "../../../backend/source/headers/backendfuncs.h"

void PrintReverse     (const Node_t *node, const char *output_file);
void PrintOriginalCode(const Node_t *node, FILE *file);
void PrintPrefixCode  (const Node_t *node, int *tab_count, FILE *file);
void PrintInfixCode   (const Node_t *node, int *tab_count, FILE *file);
void PrintPostfixCode (const Node_t *node, int *tab_count, FILE *file);
void PrintTabs        (int tab_count, FILE *file);

#endif