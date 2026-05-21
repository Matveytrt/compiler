#ifndef NASMCODE_H
#define NASMCODE_H

#include <cstddef>

#include "backendfuncs.h"

#define _BIN_BUF_SIZE_ 10000

void CtorSections       ();
void Store_S_Buf        (const char *output_file);
void Store_Bin_Buf      (const char *output_file);
void GenerateProlog     ();
void DtorSections       ();
void GenerateCode           (const Node_t *node, const char *output_file);
void Translate_AST      (const Node_t *node, char *func_name);
void PrintInfixOps      (const Node_t *node);
void PushFuncArgs       (const Node_t *node, char *func_name);
void MovVarRax          (const Node_t *node);
void WriteFunc          (const Node_t *node);
void WriteNodeInfo      (const Node_t *node);

#endif