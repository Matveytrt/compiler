#include "../headers/s_oper_funcs.h"
#include <cassert>

#define DEF_BIN_OP(op)                 \
    DECL_S_FUNC_(op)                   \
    {                                  \
        assert(node);                  \
        POP_(rbx);                     \
        POP_(rax);                     \
        op##_RR_(rax, rbx);            \
        PUSH_(rax);                    \
    }

#define DEF_CMP_OP(name, set_inst)       \
    void Do_S_##name(const Node_t *node) \
    {                                    \
        assert(node);                    \
        POP_(rbx);                       \
        POP_(rax);                       \
        CMP_RR_(rax, rbx);               \
        TEXT_("xor rax, rax");           \
        TEXT_(#set_inst " al");          \
        PUSH_(rax);                      \
    }

#define DEF_S_LABEL(name)                       \
    void Do_S_##name(Node_t *node, FILE *file)  \
    {                                           \
        assert(node);                           \
        assert(file);                           \
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

DEF_S_LABEL(IF);
DEF_S_LABEL(ELSE);
DEF_S_LABEL(WHILE);
DEF_S_LABEL(FOR);

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
    PUSH_(rax); //square
}

void Do_S_RET(const Node_t *node)
{
    assert(node);

    POP_(rbp);
    TEXT_("ret");
}

void Do_S_ASSIGN(const Node_t *node)
{
    assert(node);

    Node_t *assign_node = (IsOper(GetLeft(node), OP_V_DCLR)) ? GetLeft(GetLeft(node)) : GetLeft(node);

    if (GetVarScope(assign_node) == GLOBAL)
    {
        if (IsOper(GetParent(assign_node), OP_V_DCLR)) { Do_S_VDECL(assign_node); }

        POP_(rax);
        MOV_MR_(GetVarName(assign_node), rax);       
    }
    
    else
    {
        int var_ofs = GetVarOfs(assign_node);
        POP_(rax);
        MOV_MR_OFS_(var_ofs, rax);
    }

}

void Do_S_SKIP(const Node_t *node) {}

void Do_S_InfixIF(const Node_t *node)
{
    assert(node);

    Node_t *else_node = NULL;

    if (GetParent(node) && GetRight(GetParent(node)) && ( else_node = GetLeft(GetRight(GetParent(node))) ))
    {
        //fix
    }

    POP_(rax);
    TEST_RR_(rax, rax);
    JMP_(jz, "end_IF", node);
}

void Do_S_InfixELSE (const Node_t *node)
{
    assert(node);
    //fix
}
void Do_S_InfixWHILE (const Node_t *node)
{
    assert(node);

    POP_(rax);
    TEST_RR_(rax, rax);
    JMP_(jz, "end_IF", node);
}

void Do_S_MEMGET (const Node_t *node)
{
    assert(node);


}

void Do_S_MEMSET (const Node_t *node)
{
    assert(node);


}
void Do_S_Print (const Node_t *node)
{
    assert(node);


}

void Do_S_Scanf (const Node_t *node)
{
    assert(node);


}

void Do_S_VDECL (const Node_t *node)
{
    assert(node);

    if (GetVarScope(GetLeft(node)) == GLOBAL) DATA_("%s dq 0", GetVarName(GetLeft(node)));
}