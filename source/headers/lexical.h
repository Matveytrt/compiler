#ifndef LEXICAL_H
#define LEXICAL_H

#include "workwithfile.h"
#include "tokstack.h"
#include "treefuncs.h"

TokStack_t  TokStkCtor       ();
void        TokStkDtor       (TokStack_t *stk);
void        FuncTableDtor    ();
void        VarTableDtor     ();
void        GetTokens        (File_Info_t *info, TokStack_t *stk);
bool        GetOpToken       (char **buff, int nline, TokStack_t *stk);
void        DumpTokens       (TokStack_t *stk, int line);

int         SearchVarName    (const char *var);
int         SearchFuncName   (const char *func);
int         SkipSpaces       (char **buff);

#define INIT_VAR(capacity)      VarStackInit(&Var_table, capacity, __LINE__)
#define PUSH_VAR(val)           VarStackPush(&Var_table, val, __LINE__)
#define POP_VAR(val)            VarStackPop(&Var_table, err, __LINE__)
#define DUMP_VAR()              VarStackDump(&Var_table, __LINE__, __FILE__, "var stk")
#define DTOR_VAR()              VarStackDestroy(&Var_table, __LINE__)

#define INIT_FUNC(capacity)     FuncStackInit(&Func_table, capacity, __LINE__)
#define PUSH_FUNC(val)          FuncStackPush(&Func_table, val, __LINE__)
#define POP_FUNC(val)           FuncStackPop(&Func_table, err, __LINE__)
#define DUMP_FUNC()             FuncStackDump(&Func_table, __LINE__, __FILE__, "func stk")
#define DTOR_FUNC()             FuncStackDestroy(&Func_table, __LINE__)

#endif