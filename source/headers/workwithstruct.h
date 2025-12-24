#ifndef WORKWITHSTRUCT_H
#define WORKWITHSTRUCT_H

#include "tables.h"

Operators GetOper       (const Node_t *node);
int GetVar              (const Node_t *node);
int GetFunc             (const Node_t *node);
TreeElem_t GetNum       (const Node_t *node);
Node_t *GetLeft         (const Node_t *node);
Node_t *GetRight        (const Node_t *node);
Node_t *GetParent       (const Node_t *node);
Value_t GetData         (const Node_t *node);
NodeType_t GetType      (const Node_t *node);
void SetOper            (Node_t *node, Operators oper);
void SetFunc            (Node_t *node, int func);
void SetVar             (Node_t *node, int var);
void SetNum             (Node_t *node, TreeElem_t num);
void SetType            (Node_t *node, NodeType_t type);
void SetData            (Node_t *node, Value_t new_data);
void SetLeft            (Node_t *node, Node_t *new_node);
void SetRight           (Node_t *node, Node_t *new_node);
void SetParent          (Node_t *node, Node_t *new_node);

#endif