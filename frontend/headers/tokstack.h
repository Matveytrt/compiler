#ifndef TOKSTACK_H
#define TOKSTACK_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sys/types.h>
#include <assert.h>

#include "tokstackstruct.h"

//extern FILE *Tokstack_log;

//#define DEBUGTOK
//#define CANARY_DEBUGTOK

extern FILE *Tokstk_log;

#ifdef DEBUGTOK
    #define ONDEBUGTOKARGS(...) __VA_ARGS__
#else
    #define ONDEBUGTOKARGS(...)  
#endif

TokStackErr_t TokStackInit(TokStack_t *stk, int capacity, int line);
TokStackErr_t TokStackPush(TokStack_t *stk, TokStackElement_t value, int line);
TokStackElement_t TokStackPop(TokStack_t *stk, TokStackErr_t *error, int line);
TokStackErr_t TokStackDestroy(TokStack_t *stk, int line);
TokStackErr_t TokStackDump(TokStack_t *stk, int line, const char *filename, const char *stkname);
#endif

#ifdef DEBUGTOK
    #define ONDEBUGTOK(func) func
#else
    #define ONDEBUGTOK(func) 
#endif

#ifdef CANARY_DEBUGTOK
    #define CANDEBUGTOK(func) func
#else
    #define CANDEBUGTOK(func) 
#endif