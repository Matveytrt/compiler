#ifndef NASMCODE_H
#define NASMCODE_H

#include <cstddef>
#include "backendfuncs.h"
#include "s_oper_funcs.h"

#define _S_BUF_SIZE_ 10000
#define _BIN_BUF_SIZE_ 10000

void CtorSections       ();
void StoreBuf           (const char *output_file);
void DtorSections       ();
void MakeCode           (const Node_t *node, const char *output_file);
void Translate_AST      (const Node_t *node, char *func_name);
void PrintInfixOps      (const Node_t *node);
void WriteFunc          (const Node_t *node);
void WriteNodeInfo      (const Node_t *node);
#endif