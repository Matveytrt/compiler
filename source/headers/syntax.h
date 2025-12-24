#ifndef SYNTAX_H
#define SYNTAX_H

#include "lexical.h"

Node_t *GetGeneral      (const TokStack_t *stk);
Node_t *GetOperator     (const TokStack_t *stk, int *stk_index);
Node_t *GetFuncDeclare  (const TokStack_t *stk, int *stk_index);
Node_t *GetAssign       (const TokStack_t *stk, int *stk_index);
Node_t *GetConditional  (const TokStack_t *stk, int *stk_index);
Node_t *GetExpression   (const TokStack_t *stk, int *stk_index);
Node_t *GetTerm         (const TokStack_t *stk, int *stk_index);
Node_t *GetExp          (const TokStack_t *stk, int *stk_index);
Node_t *GetParent       (const TokStack_t *stk, int *stk_index);
Node_t *GetNumber       (const TokStack_t *stk, int *stk_index);
Node_t *GetVariable     (const TokStack_t *stk, int *stk_index);
Node_t *GetFunction     (const TokStack_t *stk, int *stk_index);

#endif