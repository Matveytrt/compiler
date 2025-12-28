#ifndef FUNCSTACKSTRUCT_H
#define FUNCSTACKSTRUCT_H

#include <stdio.h>
#include "nodestruct.h"

typedef Func_t         FuncStackElement_t;

struct FuncStack_t
{
    FuncStackElement_t  canaryleft;
    FuncStackElement_t *data;
    Ssize_t            size;
    Ssize_t            capacity;
    Ssize_t            hash;
    int                flag;
    FuncStackElement_t canaryright;
};

struct FuncStackErr_t
{
    int code;
    int line;
    int type;
};

#endif 
 