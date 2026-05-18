#ifndef TABLES_H
#define TABLES_H

#include "varstack.h"
#include "funcstack.h"
#include "string.h"

#define _OPERDATASIZE_ 38

extern FuncStack_t Func_table;
extern VarStack_t  Var_table;
extern Oper_t Oper_table[];

extern FILE *Logfile;

#endif