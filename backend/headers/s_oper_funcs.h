#ifndef S_OPER_FUNCS_H
#define S_OPER_FUNCS_H

#include "../../general/generalheaders/treefuncs.h"
#include "s_macros.h"

#define DECL_S_FUNC_(op) void Do_S_##op (const Node_t *node)

DECL_S_FUNC_(ADD);
DECL_S_FUNC_(SUB);
DECL_S_FUNC_(MUL);
DECL_S_FUNC_(DIV);
DECL_S_FUNC_(SQRT);
DECL_S_FUNC_(POW);
DECL_S_FUNC_(NOT);
DECL_S_FUNC_(AND);
DECL_S_FUNC_(OR);

DECL_S_FUNC_(EQ);
DECL_S_FUNC_(NEQ);
DECL_S_FUNC_(ABOVE_EQ);
DECL_S_FUNC_(BELOW_EQ);
DECL_S_FUNC_(ABOVE);
DECL_S_FUNC_(BELOW);

DECL_S_FUNC_(InfixIF);
DECL_S_FUNC_(InfixWHILE);

DECL_S_FUNC_(IF);
DECL_S_FUNC_(ELSE);
DECL_S_FUNC_(WHILE);
DECL_S_FUNC_(FOR);

DECL_S_FUNC_(SKIP);
DECL_S_FUNC_(ASSIGN);
DECL_S_FUNC_(MEMGET);
DECL_S_FUNC_(MEMSET);
DECL_S_FUNC_(PRINT);
DECL_S_FUNC_(SCAN);
DECL_S_FUNC_(VDECL);
DECL_S_FUNC_(PRINTCHAR);

#define S_SPRINT(sec, format, ...) S_SIZE_(sec) += (size_t) snprintf(S_DATA_(sec) + S_SIZE_(sec), S_CAP_(sec) - S_SIZE_(sec), format, ##__VA_ARGS__) 
#define TEXT_(format, ...)         S_SPRINT(TEXT_SEC, format "\n", ##__VA_ARGS__)
#define DATA_(format, ...)         S_SPRINT(DATA_SEC, format "\n", ##__VA_ARGS__)

#endif