#ifndef VARSTACKSTRUCT_H
#define VARSTACKSTRUCT_H

#include <stdio.h>
#include "nodestruct.h"

typedef Var_t         VarStackElement_t;

struct VarStack_t
{
    VarStackElement_t  canaryleft;
    VarStackElement_t *data;
    Ssize_t            size;
    Ssize_t            capacity;
    Ssize_t            hash;
    int                flag;
    VarStackElement_t  canaryright;
};

struct VarStackErr_t
{
    int code;
    int line;
    int type;
};

#endif 
 