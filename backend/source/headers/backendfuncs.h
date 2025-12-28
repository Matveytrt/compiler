#ifndef BACKENDFUNCS_H
#define BACKENDFUNCS_H

#include "../../../general/source/generalheaders/treefuncs.h"
#include "../../../general/source/generalheaders/workwithfile.h"

Node_t *ReadTreeFromFile(const char *input_tree, const char *output_tree, int line);
Node_t *ReadNode        (char *buff, int *cur_pos, const char *output_tree, int *start_index);
Node_t *CheckNodeType   (const char *str, int start_idx);
int IsNil               (const char *buff);
int SkipSpaces          (const char *buff);
void DumpVarTable       ();

#endif