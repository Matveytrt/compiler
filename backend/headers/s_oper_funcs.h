#ifndef S_OPER_FUNCS_H
#define S_OPER_FUNCS_H

#include "../../general/generalheaders/treefuncs.h"
#include "section_table.h"

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
DECL_S_FUNC_(DRAW);

#define TEXT_SEC Binary.text
#define DATA_SEC Binary.data
#define RODATA_SEC Binary.rodata

#define S_DATA_(sec)   sec.s_data
#define S_SIZE_(sec)   sec.s_size
#define S_CAP_(sec)    sec.s_cap

#define BIN_DATA_(sec) sec.bin_data
#define BIN_SIZE_(sec) sec.bin_size
#define BIN_CAP_(sec)  sec.bin_cap

#define S_SPRINT(sec, format, ...) S_SIZE_(sec) += (size_t) snprintf(S_DATA_(sec) + S_SIZE_(sec), S_CAP_(sec) - S_SIZE_(sec), format, ##__VA_ARGS__) 
#define TEXT_(format, ...)         S_SPRINT(TEXT_SEC, format "\n", ##__VA_ARGS__)
#define DATA_(format, ...)         S_SPRINT(DATA_SEC, format "\n", ##__VA_ARGS__)

#define PUSH_(reg)              TEXT_("push %s", #reg)
#define POP_(reg)               TEXT_("pop %s", #reg)

#define SHL_(reg, ofs)          TEXT_("shl %s, %d", #reg, ofs)
#define SHR_(reg, ofs)          TEXT_("shr %s, %d", #reg, ofs)
#define ADD_RR_(dst, src)       TEXT_("add %s, %s", #dst, #src)
#define ADD_RI_(dst, src)       TEXT_("add %s, %d", #dst, src)
#define SUB_RR_(dst, src)       TEXT_("sub %s, %s", #dst, #src)
#define SUB_RI_(dst, src)       TEXT_("sub %s, %d", #dst, src)
#define MUL_RR_(dst, src)       TEXT_("imul %s, %s", #dst, #src)
#define MUL_RI_(dst, src)       TEXT_("imul %s, %d", #dst, src)
#define DIV_RR_(dst, src)       TEXT_("idiv %s, %s", #dst, #src)
#define DIV_RI_(dst, src)       TEXT_("idiv %s, %d", #dst, src)

#define CMP_RR_(reg1, reg2)     TEXT_("cmp %s, %s", #reg1, #reg2)
#define CMP_RI_(reg, num)       TEXT_("cmp %s, %d", #reg, num)
#define TEST_RR_(reg1, reg2)    TEXT_("test %s, %s", #reg1, #reg2)

#define AND_RR_(dst, src)       TEXT_("and %s, %s", #dst, #src)
#define AND_RI_(dst, src)       TEXT_("and %s, %d", #dst, src)
#define OR_RR_(dst, src)        TEXT_("or %s, %s", #dst, #src)
#define OR_RI_(dst, src)        TEXT_("or %s, %d", #dst, src)
#define NOT_R(reg)              TEXT_("not %s", #reg)
#define NOT_I(val)              TEXT_("not %d", val)

#define MOV_RR_(dst, src)       TEXT_("mov %s, %s", #dst, #src)
#define MOV_RI_(dst, src)       TEXT_("mov %s, %d", #dst, src)
#define MOV_RM_(dst, src)       TEXT_("mov %s, [%s]", #dst, #src)
#define MOV_MR_(dst, src)       TEXT_("mov [%s], %s", #dst, #src)
#define LEA_(dst, src)          TEXT_("lea %s, [%s]", #dst, #src)

#define MOV_RM_OFS_(dst, ofs)   MOV_RI_(rcx, ofs); \
                                TEXT_("mov %s, [rbp + rcx]", #dst)

#define MOV_MR_OFS_(ofs, src)   MOV_RI_(rcx, ofs); \
                                TEXT_("mov [rbp + rcx], %s", #src)

#define CALL_(func)             TEXT_("call %s", func)
#define LBL_(name, ptr)         TEXT_("%s_%p:", name, ptr)
#define TAG_(name)              TEXT_("%s:", name)
#define JMP_(cond, lbl, ptr)    TEXT_("%s %s_%p", #cond, lbl, ptr)



#endif