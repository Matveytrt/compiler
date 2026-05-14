#ifndef ASMCODE_H
#define ASMCODE_H

#include "backendfuncs.h"
#include "../../general/generalheaders/operfuncs.h"

void MakeAsm                (Node_t *node, const char *output_file);
void PrintAsmCode           (Node_t *node, FILE *file);
void FillVarInfo            (FILE *file, VarStack_t *stk, int start_index, int end_index);

void PrintFunc              (Node_t *node, FILE *file);
void FillFuncArgs           (Node_t *node, FILE *file, int start_idx);
void PrintFuncCode          (Node_t *node, FILE *file, int start_idx);
void PushFuncVar            (Node_t *node, FILE *file, int start_idx);
void PopFuncVar             (Node_t *node, FILE *file, int start_idx);
void PrintFuncPostfixOpers  (Node_t *node, FILE *file, int start_idx);

#endif