#ifndef FuncSTACK_H
#define FuncSTACK_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sys/types.h>
#include <assert.h>

#include "funcstackstruct.h"

//#define DEBUGFUNC
//#define CANARY_DEBUGFUNC

extern FILE *Funcstk_log;

#ifdef DEBUGFUNC
    #define ONDEBUGFUNCARGS(...) __VA_ARGS__
#else
    #define ONDEBUGFUNCARGS(...)  
#endif

FuncStackErr_t FuncStackInit(FuncStack_t *stk, int capacity, int line);
FuncStackErr_t FuncStackPush(FuncStack_t *stk, FuncStackElement_t value, int line);
FuncStackElement_t FuncStackPop(FuncStack_t *stk, FuncStackErr_t *error, int line);
FuncStackErr_t FuncStackDestroy(FuncStack_t *stk, int line);
FuncStackErr_t FuncStackDump(FuncStack_t *stk, int line, const char *filename, const char *stkname);
#endif

#ifdef DEBUGFUNC
    #define ONDEBUGFUNC(func) func
#else
    #define ONDEBUGFUNC(func) 
#endif

#ifdef CANARY_DEBUGFUNC
    #define CANDEBUGFUNC(func) func
#else
    #define CANDEBUGFUNC(func) 
#endif