#ifndef TOKSTACKSTRUCT_H
#define TOKSTACKSTRUCT_H

#include "../../general/generalheaders/nodestruct.h"
#include <stdio.h>

typedef Node_t*         TokStackElement_t;

struct TokStack_t
{
    TokStackElement_t  canaryleft;
    TokStackElement_t *data;
    Ssize_t            size;
    Ssize_t            capacity;
    Ssize_t            hash;
    int                flag;
    TokStackElement_t  canaryright;
};

struct TokStackErr_t
{
    int code;
    int line;
    int type;
};

#endif 
 