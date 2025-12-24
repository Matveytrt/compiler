#ifndef VARSTACK_H
#define VARSTACK_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sys/types.h>
#include <assert.h>

#include "varstackstruct.h"

//#define DEBUGVAR
//#define CANARY_DEBUGVAR

#ifdef DEBUGVAR
    #define ONDEBUGVARARGS(...) __VA_ARGS__
#else
    #define ONDEBUGVARARGS(...)  
#endif

extern FILE *Varstk_log;

VarStackErr_t VarStackInit(VarStack_t *stk, int capacity, int line);
VarStackErr_t VarStackPush(VarStack_t *stk, VarStackElement_t value, int line);
VarStackElement_t VarStackPop(VarStack_t *stk, VarStackErr_t *error, int line);
VarStackErr_t VarStackDestroy(VarStack_t *stk, int line);
VarStackErr_t VarStackDump(VarStack_t *stk, int line, const char *filename, const char *stkname);
#endif

#ifdef DEBUGVAR
    #define ONDEBUGVAR(func) func
#else
    #define ONDEBUGVAR(func) 
#endif

#ifdef CANARY_DEBUGVAR
    #define CANDEBUGVAR(func) func
#else
    #define CANDEBUGVAR(func) 
#endif