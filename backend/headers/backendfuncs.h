#ifndef BACKENDFUNCS_H
#define BACKENDFUNCS_H

#include "../../general/generalheaders/treefuncs.h"
#include "../../general/generalheaders/workwithfile.h"

#define _ARGS_OFS_ 16
#define _REG_SIZE_ 8

Node_t *ReadTreeFromFile(const char *input_tree, const char *output_tree, int line);
Node_t *ReadNode        (char *buff, int *cur_pos, const char *output_tree, int *start_index);
void    SetScopes       (Node_t *node, int scope, int arg_end_idx);
int     SetArgScopes    (Node_t *node, int arg_ofs, int *arg_end_idx);
Node_t *CheckNodeType   (const char *str, int start_idx);
int     IsNil           (const char *buff);
int     SkipSpaces      (const char *buff);
void    DumpVarTable    ();
void    DumpFuncTable   ();

#endif