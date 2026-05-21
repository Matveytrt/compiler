#include "../generalheaders/tables.h"
#include "../generalheaders/operfuncs.h"

#define LANG_NAME_INIT_(name) name, strlen(name)
#define MATH_OP_INIT(op, name, order_type) {OP_##op, "_MATH_" #op "_", #name, strlen(#name), order_type, Do_VM_SKIP, Do_VM_##op} 
#define MATH_OP_INIT2(op, name, order_type) {OP_##op, "_MATH_" #op "_", #name, strlen(#name), order_type, Do_VM_SKIP, Do_VM_SKIP} //half ready
#define MATH_OP_INIT3(op, name, order_type) {OP_##op, "_MATH_" #op "_", #name, strlen(#name), order_type, Do_VM_SKIP, Do_VM_SKIP} //not ready
#define BR_OP_INIT(op, std_name, name) {op, std_name, name, strlen(name), OTHER_ORD, Do_VM_SKIP, Do_VM_SKIP}


Oper_t Oper_table [_OPERDATASIZE_] =    {
                                            MATH_OP_INIT(ADD, RAISE, INFIX_ORD),
                                            MATH_OP_INIT(SUB, FOLD, INFIX_ORD),
                                            MATH_OP_INIT(MUL, ALLIN, INFIX_ORD),
                                            MATH_OP_INIT(DIV, CUT, INFIX_ORD),
                                            MATH_OP_INIT(SQRT, SQRT, INFIX_ORD),
                                            MATH_OP_INIT2(POW, POW, INFIX_ORD),
                                            MATH_OP_INIT2(EQ, SNAP, INFIX_ORD),
                                            MATH_OP_INIT2(NEQ, MUCK, INFIX_ORD),
                                            MATH_OP_INIT2(ABOVE_EQ, BUMP, INFIX_ORD),
                                            MATH_OP_INIT2(BELOW_EQ, TANK, INFIX_ORD),
                                            MATH_OP_INIT2(BELOW, TILT, INFIX_ORD),
                                            MATH_OP_INIT2(ABOVE, SHOVE, INFIX_ORD),
                                            MATH_OP_INIT2(NOT, NOT, OTHER_ORD),
                                            MATH_OP_INIT2(AND, PAIR, OTHER_ORD),
                                            MATH_OP_INIT2(OR, SUIT, OTHER_ORD),
                                            BR_OP_INIT(OPEN_R_BR, "(", "("),
                                            BR_OP_INIT(CLOSE_R_BR, ")", ")"),
                                            BR_OP_INIT(OPEN_SQ_BR, "[", "BUYIN"),
                                            BR_OP_INIT(CLOSE_SQ_BR, "]", "CASHOUT"),
                                            BR_OP_INIT(OPEN_FIG_BR, "{", "ANTE"),
                                            BR_OP_INIT(CLOSE_FIG_BR, "}", "POT"),
                                        {OP_IF,         "_IF_",                  LANG_NAME_INIT_("BLUFF?"),     PREFIX_ORD,      Do_VM_InfixIF,      Do_VM_IF,},
                                        {OP_ELSE,       "_ELSE_",                LANG_NAME_INIT_("CHECKBACK"),  PREFIX_ORD,      Do_VM_InfixELSE,    Do_VM_ELSE,},
                                        {OP_WHILE,      "_WHILE_",               LANG_NAME_INIT_("WHILE"),      PREFIX_ORD,      Do_VM_InfixWHILE,   Do_VM_WHILE,},
                                        {OP_FOR,        "_FOR_",                 LANG_NAME_INIT_("FOR"),        PREFIX_ORD,      Do_VM_SKIP,         Do_VM_SKIP,},
                                        {OP_RET,        "_RETURN_",              LANG_NAME_INIT_("BOUNTY"),     PREFIX_ORD,      Do_VM_SKIP,         Do_VM_RET,},
                                        {OP_BREAK,      "_BREAK_",               LANG_NAME_INIT_("PASS"),       PREFIX_ORD,      Do_VM_SKIP,         Do_VM_RET,},//brrr asm
                                        {OP_ASSIGN,     "_ASSIGNMENT_",          LANG_NAME_INIT_("BET"),        INFIX_ORD,       Do_VM_SKIP,         Do_VM_ASSIGN},
                                        {OP_END,        "$",                     LANG_NAME_INIT_("TURN"),       OTHER_ORD,       Do_VM_SKIP,         Do_VM_SKIP,},
                                        {OP_F_DCLR,     "_FUNC_DECLARE_",        LANG_NAME_INIT_("BUYSTRAT"),   PREFIX_ORD,      Do_VM_SKIP,         Do_VM_SKIP,},
                                        {OP_V_DCLR,     "_VAR_DECLARE_",         LANG_NAME_INIT_("FREEBET"),    PREFIX_ORD,      Do_VM_SKIP,         Do_VM_SKIP,},
                                        {OP_COMMA,      "_COMMA_",               LANG_NAME_INIT_(","),          INFIX_ORD,       Do_VM_SKIP,         Do_VM_SKIP,},
                                        {OP_STR_END,    "_END_STATEMENT_",       LANG_NAME_INIT_("$"),          INFIX_ORD,       Do_VM_SKIP,         Do_VM_SKIP,},
                                        {OP_PRINT,      "_PRINT_",               LANG_NAME_INIT_("CALL"),       PREFIX_ORD,      Do_VM_SKIP,         Do_VM_Print,},
                                        {OP_SCAN,       "_SCAN_",                LANG_NAME_INIT_("READ"),       PREFIX_ORD,      Do_VM_SKIP,         Do_VM_Scanf,},
                                        {OP_MEMGET,     "MEMGET",                LANG_NAME_INIT_("MEMGET"),     PREFIX_ORD,      Do_VM_SKIP,         Do_VM_MEMGET,},
                                        {OP_MEMSET,     "MEMSET",                LANG_NAME_INIT_("MEMSET"),     PREFIX_ORD,      Do_VM_SKIP,         Do_VM_MEMSET,},
                                        {OP_PRINTCHAR,  "_PUTCHAR_",             LANG_NAME_INIT_("PRINTCHAR"),  PREFIX_ORD,      Do_VM_SKIP,         Do_VM_SKIP},
                                        };
VarStack_t Var_table = {};
FuncStack_t Func_table = {};
FILE *Logfile = NULL;
