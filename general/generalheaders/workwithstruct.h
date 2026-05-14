#ifndef WORKWITHSTRUCT_H
#define WORKWITHSTRUCT_H

#include "nodestruct.h"
#include "tables.h"

inline Operators    GetOper         (const Node_t *node) { return node->data.oper; }
inline void         Do_S_Oper       (const Node_t *node) {Oper_table[GetOper(node)].ptr_s_func(node);}
inline int          GetVar          (const Node_t *node) { return node->data.var; }
inline char        *GetVarName      (const Node_t *node) { return Var_table.data[GetVar(node)].name; }
inline int          GetVarOfs       (const Node_t *node) { return Var_table.data[GetVar(node)].ofs; }
inline int          GetVarScope     (const Node_t *node) { return Var_table.data[GetVar(node)].scope; }
inline int          GetFunc         (const Node_t *node) { return node->data.func; }
inline char        *GetFuncName     (const Node_t *node) { return Func_table.data[GetFunc(node)].name; }
inline int          GetFuncStartIdx (const Node_t *node) { return Func_table.data[GetFunc(node)].start_idx; }
inline int          GetFuncEndIdx   (const Node_t *node) { return Func_table.data[GetFunc(node)].end_idx; }
inline int          GetFuncArgEndIdx(const Node_t *node) { return Func_table.data[GetFunc(node)].arg_end_idx; }
inline TreeElem_t   GetNum          (const Node_t *node) { return node->data.num; }
inline Node_t      *GetLeft         (const Node_t *node) { return node->left; }
inline Node_t      *GetRight        (const Node_t *node) { return node->right; }
inline Node_t      *GetParent       (const Node_t *node) { return node->parent; }
inline Value_t      GetData         (const Node_t *node) { return node->data; }
inline NodeType_t   GetType         (const Node_t *node) { return node->type; }
const char         *GetVarScopeName (int scope);

void                SetData         (Node_t *node, Value_t new_data);
inline void         SetType         (Node_t *node, NodeType_t type)     { node->type = type; }
inline void         SetOper         (Node_t *node, Operators oper)      { node->data.oper = oper; }
inline void         SetVar          (Node_t *node, int var)             { node->data.var = var; }
inline void         SetVarOfs       (Node_t *node, int ofs)             { Var_table.data[GetVar(node)].ofs = ofs; }
inline void         SetVarScope     (Node_t *node, int scope)           { Var_table.data[GetVar(node)].scope = scope; }
inline void         SetNum          (Node_t *node, TreeElem_t num)      { node->data.num = num; }
inline void         SetFunc         (Node_t *node, int func)            { node->data.func = func; }
inline void         SetLeft         (Node_t *node, Node_t *new_node)    { node->left = new_node; }
inline void         SetRight        (Node_t *node, Node_t *new_node)    { node->right = new_node; }
inline void         SetParent       (Node_t *node, Node_t *new_node)    { node->parent = new_node; }

#endif