#ifndef S_OPER_FUNCS_H
#define S_OPER_FUNCS_H

#include "../../general/generalheaders/treefuncs.h"
#include "nasmcode.h"
#include "s_macros.h"

void Emit_Oper(const Node_t *node, char *func_name);
void Emit_Infix_Oper(const Node_t *node, char *func_name);
void Emit_ASSIGN(const Node_t *node, char *func_name);

void Emit_SQRT(const Node_t *node);
void Emit_VDECL(const Node_t *node);
void Emit_MEMGET(const Node_t *node);
void Emit_MEMSET(const Node_t *node, char *func_name);
void Emit_PRINT(const Node_t *node);
void Emit_PRINTCHAR(const Node_t *node);
void Emit_SCAN(const Node_t *node);
void Emit_RETURN(const Node_t *node, char *func_name);

void Emit_IF(const Node_t *node, char *func_name);
void Emit_IF_Epilog(const Node_t *node);
void Emit_ELSE(const Node_t *node, char *func_name);
void Emit_WHILE(const Node_t *node, char *func_name);
void Emit_WHILE_Epilog(const Node_t *node);
void Emit_FOR(const Node_t *node, char *func_name);


#endif