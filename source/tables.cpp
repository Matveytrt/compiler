#include "tables.h"

Oper_t Oper_table [_OPERDATASIZE_] =    {
                                        {"+",       "_MATH_ADD_",           OP_ADD,             strlen("+"),     INFIX_ORD},
                                        {"-",       "_MATH_SUB_",           OP_SUB,             strlen("-"),     INFIX_ORD},
                                        {"*",       "_MATH_MUL_",           OP_MUL,             strlen("*"),     INFIX_ORD},
                                        {"/",       "_MATH_DIV_",           OP_DIV,             strlen("/"),     INFIX_ORD},
                                        {"sqrt",    "_MATH_SQRT_",          OP_SQRT,            strlen("sqrt"),  PREFIX_ORD},
                                        {"^",       "_MATH_POW_",           OP_POW,             strlen("^"),     INFIX_ORD},
                                        {"==",      "_MATH_EQUAL_",         OP_EQ,              strlen("=="),    OTHER_ORD},
                                        {"!=",      "_MATH_NOT_EQUAL_",     OP_NEQ,             1,               OTHER_ORD},
                                        {"<",       "_MATH_BELOW_",         OP_BELOW,           1,               OTHER_ORD},
                                        {">",       "_MATH_ABOVE_",         OP_ABOVE,           1,               OTHER_ORD},
                                        {">=",      "_MATH_ABOVE_EQ_",      OP_ABOVE_EQ,        1,               OTHER_ORD},
                                        {"<=",      "_MATH_BELOW_EQ_",      OP_BELOW_EQ,        1,               OTHER_ORD},
                                        {"!",       "_MATH_NOT_",           OP_NOT,             1,               OTHER_ORD},
                                        {"&",       "_MATH_AND_",           OP_AND,             1,               OTHER_ORD},
                                        {"||",      "_MATH_OR_",            OP_OR,              1,               OTHER_ORD},
                                        {"(",       "(",                    OPEN_R_BR,          1,               OTHER_ORD},
                                        {")",       ")",                    CLOSE_R_BR,         1,               OTHER_ORD},
                                        {"[",       "[",                    OPEN_SQ_BR,         1,               OTHER_ORD},
                                        {"]",       "]",                    CLOSE_SQ_BR,        1,               OTHER_ORD},
                                        {"{",       "{",                    OPEN_FIG_BR,        1,               OTHER_ORD},
                                        {"}",       "}",                    CLOSE_FIG_BR,       1,               OTHER_ORD},
                                        {"if",      "_IF_",                 OP_IF,              strlen("if"),    OTHER_ORD},
                                        {"else",    "_ELSE_",               OP_ELSE,            strlen("else"),  OTHER_ORD},
                                        {"while",   "_WHILE_",              OP_WHILE,           strlen("while"), OTHER_ORD},
                                        {"for",     "_FOR_",                OP_FOR,             strlen("for"),   OTHER_ORD},
                                        {"return",  "_RETURN_",             OP_RET,             strlen("return"),OTHER_ORD},
                                        {"break",   "_BREAK_",              OP_BREAK,           strlen("break"), OTHER_ORD},
                                        {"=",       "_ASSIGNMENT_",         OP_ASSIGN,          1,               OTHER_ORD},
                                        {"$",       "$",                    OP_END,             1,               OTHER_ORD},
                                        {"dfunc",   "_FUNC_DECLARE_",       OP_F_DCLR,          strlen("dfunc"), OTHER_ORD},
                                        {"dvar",    "_VAR_DECLARE_",        OP_V_DCLR,          strlen("dvar"),  OTHER_ORD},
                                        {",",       "_COMMA_",              OP_COMMA,           1,               OTHER_ORD},
                                        {";",       "_END_STATEMENT_",      OP_STR_END,         1,               OTHER_ORD},
                                        };

VarStack_t Var_table = {};
FuncStack_t Func_table = {};
FILE *Logfile = NULL;
