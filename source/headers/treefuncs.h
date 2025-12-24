#ifndef TREEFUNCS_H
#define TREEFUNCS_H

#include "global.h"
#include "workwithstruct.h"
#include <math.h>

Node_t *NodeCtor        ();
Node_t *CtorOperation   (Operators oper);
Node_t *CtorFunc        (int func);
Node_t *CtorVariable    (int var);
Node_t *CtorNumber      (TreeElem_t number);

Node_t *NodeCpy         (const Node_t *node);
Node_t *NewNode         (Node_t *node, Node_t *left_node, Node_t *right_node);
Node_t *RemoveFictNode  (Node_t *node, int *change_par);
Node_t *RemoveFict      (Node_t *node, int *change_par);
void    NodeDtor        (Node_t *node);

bool IsZero             (double value);
bool IsNumType          (const Node_t *node);
bool IsVarType          (const Node_t *node);
bool IsOperType         (const Node_t *node);
bool IsFuncType         (const Node_t *node);
bool IsNum              (const Node_t *node, TreeElem_t value);
bool IsVar              (const Node_t *node, int var);
bool IsOper             (const Node_t *node, Operators oper);
bool IsPrefix           (const Node_t *node);
bool IsInfix            (const Node_t *node);
bool IsConditionalOp    (const Node_t *node);
bool IsInt              (TreeElem_t value);

void PrintNode              (const Node_t *node, FILE *graph, FILE *tree_file);
void TreeDump               (const Node_t *node, const char *out_tree, int line);

#define CTOR_OP(oper)           CtorOperation(oper)
#define CTOR_NUM(num)           CtorNumber   (num)
#define CTOR_FUNC(func)         CtorFunc     (func) 
#define CTOR_VAR(var)           CtorVariable (var)  

#define LOGINFO(info)   fprintf(Logfile, "<h3>\n\t<font color = blue> ");   \
                        fprintf(Logfile,  info);                            \
                        fprintf(Logfile, " </font>\n</h3>\n")

#define Dump(node, info)                         \
            LOGINFO(info);                       \
            TreeDump(node, "out.txt", __LINE__)

#endif