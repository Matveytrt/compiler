#ifndef ASMCODE_H
#define ASMCODE_H

#include "backendfuncs.h"

void MakeAsm            (Node_t *node, const char *output_file);
void FillVarInfo        (FILE *file, VarStack_t *stk, int start_index);
void PrintAsmCode       (Node_t *node, FILE *file);
void PrintPrefixOpers   (Node_t *node, FILE *file);
void PrintInfixOpers    (Node_t *node, FILE *file);
void PrintPostfixOpers  (Node_t *node, FILE *file);
void PrintFunc          (Node_t *node, FILE *file);
void FillFuncArgs       (Node_t *node, FILE *file);

#endif