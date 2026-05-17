#include "../headers/s_oper_funcs.h"
#include <cassert>
#include <cstdio>

#define DEF_BIN_OP(op)                 \
    DECL_S_FUNC_(op)                   \
    {                                  \
        assert(node);                  \
        POP_(rcx);                     \
        POP_(rax);                     \
        op##_RR_(rax, rcx);            \
        PUSH_(rax);                    \
    }

#define DEF_CMP_OP(name, set_inst)       \
    void Do_S_##name(const Node_t *node) \
    {                                    \
        assert(node);                    \
        POP_(rcx);                       \
        POP_(rax);                       \
        CMP_RR_(rax, rcx);               \
        TEXT_(#set_inst " al");          \
        AND_RI_(rax, 0x1);               \
        PUSH_(rax);                      \
    }

#define DEF_S_LABEL(name)                       \
    void Do_S_##name(const Node_t *node)        \
    {                                           \
        assert(node);                           \
        LBL_("end_" #name, node);               \
    }

DEF_BIN_OP(ADD);
DEF_BIN_OP(SUB);
DEF_BIN_OP(MUL);
DEF_BIN_OP(DIV);
DEF_BIN_OP(AND);
DEF_BIN_OP(OR);

DEF_CMP_OP(EQ, sete);
DEF_CMP_OP(NEQ, setne);
DEF_CMP_OP(BELOW, setl);
DEF_CMP_OP(ABOVE, setg);
DEF_CMP_OP(BELOW_EQ, setle);
DEF_CMP_OP(ABOVE_EQ, setge);

DEF_S_LABEL(ELSE);
DEF_S_LABEL(FOR);

void Do_S_IF(const Node_t *node)
{
    assert(node);

    Node_t *else_node = NULL;

    if (GetParent(node) && GetRight(GetParent(node)) && ( else_node = GetLeft(GetRight(GetParent(node))) ) 
        && IsOper(else_node, OP_ELSE)) JMP_(jmp, "end_ELSE", else_node);

    LBL_("end_IF", node);
}

void Do_S_WHILE(const Node_t *node)
{
    assert(node);

    JMP_(jmp, "WHILE", node);
    LBL_("end_WHILE", node);
}

void Do_S_NOT(const Node_t *node)
{
    assert(node);

    POP_(rax);
    NOT_R(rax);
    PUSH_(rax); 
}

void Do_S_SQRT(const Node_t *node)
{
    assert(node);

    POP_(rax);
    TEXT_("cvtsi2sd xmm0, rax");
    TEXT_("sqrtsd xmm0, xmm0");
    TEXT_("cvttsd2si rax, xmm0");
    PUSH_(rax);
}

void Do_S_POW(const Node_t *node)
{
    assert(node);

    POP_(rax);
    MUL_RR_(rax, rax);
    PUSH_(rax);
}

void Do_S_ASSIGN(const Node_t *node)
{
    assert(node);

    Node_t *assign_node = (IsOper(GetLeft(node), OP_V_DCLR)) ? GetLeft(GetLeft(node)) : GetLeft(node);

    if (GetVarScope(assign_node) == GLOBAL)
    {
        if (IsOper(GetParent(assign_node), OP_V_DCLR)) { DATA_("%s dq 0", GetVarName(assign_node)); }

        POP_(rax);
        TEXT_("mov [%s], rax", GetVarName(assign_node));
}
    
    else
    {
        int var_ofs = GetVarOfs(assign_node);
        POP_(rax);
        MOV_MR_OFS_(var_ofs, rax);
    }

}

void Do_S_SKIP(const Node_t *node) { assert(node); }

void Do_S_InfixIF(const Node_t *node)
{
    assert(node);

    POP_(rax);
    TEST_RR_(al, al);
    JMP_(jz, "end_IF", node);
}

void Do_S_InfixWHILE (const Node_t *node)
{
    assert(node);

    POP_(rax);
    TEST_RR_(al, al);
    JMP_(jz, "end_WHILE", node);
}

void Do_S_MEMGET (const Node_t *node)
{
    assert(node);

    POP_(rbx); //idx
    LEA_(r8, vmem_buf);
    MOV_RM_(rax, r8 + rbx);
    PUSH_(rax);
}

void Do_S_MEMSET (const Node_t *node)
{
    assert(node);

    POP_(rax); //ascii
    POP_(rbx); //idx
    LEA_(r8, vmem_buf);
    MOV_MR_(r8 + rbx, rax);
}

void Do_S_PRINT (const Node_t *node)
{
    assert(node);

    LEA_(rdi, fmt_int);
    POP_(rax);
    MOV_RR_(rsi, rax);
    TEXT_("xor rax, rax");
    CALL_("printf WRT ..plt");
}

void Do_S_SCAN (const Node_t *node)
{
    assert(node);

    CALL_("my_scanf WRT ..plt");
    MOV_MR_OFS_(GetVarOfs(GetLeft(node)), rax);
}

void Do_S_VDECL (const Node_t *node)
{
    assert(node);

    if (GetVarScope(GetLeft(node)) == GLOBAL) DATA_("%s dq 0", GetVarName(GetLeft(node)));
}

DECL_S_FUNC_(DRAW) {}