#ifndef NODESTRUCT_H
#define NODESTRUCT_H

#include <sys/types.h>

typedef int TreeElem_t;
typedef signed long int Ssize_t;

enum NodeType_t
{
    TYPE_OP    = 0,
    TYPE_VAR   = 1,
    TYPE_NUM   = 2,
    TYPE_UFUNC = 3,
    TYPE_ERR   = 4,
};

enum Order_Types
{
    INFIX_ORD,
    PREFIX_ORD,
    POSTFIX_ORD,
    DOUBLE_ORD,
    OTHER_ORD,
};

enum Operators 
{
    OP_ADD       = 0,
    OP_SUB       = 1,
    OP_MUL       = 2,
    OP_DIV       = 3,
    OP_SQRT      = 4,
    OP_POW       = 5,

    OP_EQ        = 6,
    OP_NEQ       = 7,
    OP_ABOVE_EQ  = 8,
    OP_BELOW_EQ  = 9,
    OP_BELOW     = 10,
    OP_ABOVE     = 11,
    OP_NOT       = 12,
    OP_AND       = 13,
    OP_OR        = 14,

    OPEN_R_BR    = 15,
    CLOSE_R_BR   = 16,
    OPEN_SQ_BR   = 17,
    CLOSE_SQ_BR  = 18,
    OPEN_FIG_BR  = 19,
    CLOSE_FIG_BR = 20,

    OP_IF        = 21,
    OP_ELSE      = 22,
    OP_WHILE     = 23,
    OP_FOR       = 24,
    
    OP_RET       = 25,
    OP_BREAK     = 26,
    OP_ASSIGN    = 27,
    OP_END       = 28,
    OP_F_DCLR    = 29,
    OP_V_DCLR    = 30,
    OP_COMMA     = 31,
    OP_STR_END   = 32,
    OP_PRINT     = 33,
    OP_SCAN      = 34,
    OP_MEMGET    = 35,
    OP_MEMSET    = 36,
};

struct Var_t
{
    char *      name;
    TreeElem_t  value;
    size_t      len;
    size_t      hash;
};

struct Func_t
{
    char *      name;
    size_t      len;
    size_t      hash;
};

union Value_t
{
    Operators  oper;
    TreeElem_t num;
    int        var;
    int        func;
};

struct Lexical_t
{
    const char *cur_pos;
    int         nline;
};

struct Node_t
{
    NodeType_t type;
    Value_t    data;
    Node_t    *parent;
    Node_t    *left;
    Node_t    *right;
    Lexical_t  info;
};

struct Oper_t
{
    const char *name;
    const char *std_name;
    Operators   code;
    size_t      len;
    int         order_type;
    void        (*ptr_prefix)  (Node_t *, FILE *);
    void        (*ptr_infix)  (Node_t *, FILE *);
    void        (*ptr_postix) (Node_t *, FILE *);
    size_t      hash;
};

#endif