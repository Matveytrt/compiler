#include "../headers/s_oper_funcs.h"
#include <cassert>
#include <cstdio>

#define DEF_BIN_OP(op)                 \
    DECL_S_FUNC_(op)                   \
    {                                  \
        assert(node);                  \
        POP_(RCX);                     \
        POP_(RAX);                     \
        ADD_RR_(RAX, RCX);             \
        PUSH_(RAX);                    \
    }

#define DEF_BIN_OP_SINGLE(op)          \
    DECL_S_FUNC_(op)                   \
    {                                  \
        assert(node);                  \
        POP_(RCX);                     \
        POP_(RAX);                     \
        CQO_();                        \
        DIV_R_(RCX);                   \
        PUSH_(RAX);                    \
    }

#define DEF_S_LABEL(name)                       \
    void Do_S_##name(const Node_t *node)        \
    {                                           \
        assert(node);                           \
        LBL_BIN("end_" #name, node);            \
    }

#define DEF_CMP_OP(name, set_inst, set_op)           \
    void Do_S_##name(const Node_t *node)             \
    {                                                \
        assert(node);                                \
        POP_(RCX);                                   \
        POP_(RAX);                                   \
        CMP_RR_(RAX, RCX);                           \
        TEXT_(#set_inst " al");                      \
        BIN_SETCC(set_op, REG_AL);                   \
        MOVZX_RR_(RAX, AL);                          \
        PUSH_(RAX);                                  \
    }

DEF_CMP_OP(EQ, sete, SET_E);
DEF_CMP_OP(NEQ, setne, SET_NE);
DEF_CMP_OP(BELOW, setl, SET_L);
DEF_CMP_OP(ABOVE, setg, SET_G);
DEF_CMP_OP(BELOW_EQ, setle, SET_LE);
DEF_CMP_OP(ABOVE_EQ, setge, SET_GE);
    
DEF_BIN_OP(ADD);
DEF_BIN_OP(SUB);
DEF_BIN_OP(MUL);
DEF_BIN_OP_SINGLE(DIV);
DEF_BIN_OP(AND);
DEF_BIN_OP(OR);

DEF_S_LABEL(ELSE);
DEF_S_LABEL(FOR); //fix

void Do_S_IF(const Node_t *node)
{
    assert(node);

    Node_t *else_node = NULL;

    if (GetParent(node) && GetRight(GetParent(node)) && ( else_node = GetLeft(GetRight(GetParent(node))) ) 
        && IsOper(else_node, OP_ELSE)) {
        JMP_BIN(0xEB, "end_ELSE", else_node);
    }

    LBL_BIN("end_IF", node);
}

void Do_S_WHILE(const Node_t *node)
{
    assert(node);

    JMP_SHORT_BIN(0xEB, "start_WHILE", node);
    LBL_BIN("end_WHILE", node);
}

void Do_S_NOT(const Node_t *node)
{
    assert(node);

    POP_(RAX);
    NOT_R_(RAX);
    PUSH_(RAX); 
}

void Do_S_SQRT(const Node_t *node)
{
    assert(node);

    POP_(RAX);

    TEXT_("cvtsi2sd xmm0, rax");

    EMIT_BYTE(BIN_TEXT, 0xF2);
    EMIT_BYTE(BIN_TEXT, 0x0F);
    EMIT_BYTE(BIN_TEXT, 0x2A);
    EMIT_BYTE(BIN_TEXT, 0xC0);

    TEXT_("sqrtsd xmm0, xmm0");

    EMIT_BYTE(BIN_TEXT, 0xF2);
    EMIT_BYTE(BIN_TEXT, 0x0F);
    EMIT_BYTE(BIN_TEXT, 0x51);
    EMIT_BYTE(BIN_TEXT, 0xC0);

    TEXT_("cvttsd2si rax, xmm0");

    EMIT_BYTE(BIN_TEXT, 0xF2);
    EMIT_BYTE(BIN_TEXT, 0x0F);
    EMIT_BYTE(BIN_TEXT, 0x2C);
    EMIT_BYTE(BIN_TEXT, 0xC0);

    PUSH_(RAX);
}

void Do_S_POW(const Node_t *node)
{
    assert(node);

    POP_(RAX);
    MUL_RR_(RAX, RAX);
    PUSH_(RAX);
}

void Do_S_ASSIGN(const Node_t *node)
{
    assert(node);

    Node_t *assign_node = (IsOper(GetLeft(node), OP_V_DCLR)) ? GetLeft(GetLeft(node)) : GetLeft(node);

    if (GetVarScope(assign_node) == GLOBAL)
    {
        if (IsOper(GetParent(assign_node), OP_V_DCLR)) 
        { 
            DATA_("%s dq 0", GetVarName(assign_node));
            AddPatch(GetVarName(assign_node));
        }

        POP_(RAX);
        // TODO: binary label address resolution for global variable
        MOV_MR_LABEL_(GetVarName(assign_node), RAX);
    }
    else
    {
        int var_ofs = GetVarOfs(assign_node);
        POP_(RAX);
        MOV_MR_OFS_(var_ofs, RAX);
    }
}

void Do_S_SKIP(const Node_t *node) { assert(node); }

void Do_S_InfixIF(const Node_t *node)
{
    assert(node);

    POP_(RAX);
    TEST_RR_(AL, AL);
    JMP_BIN(0x84, "end_IF", node);
}

void Do_S_InfixWHILE (const Node_t *node)
{
    assert(node);

    LBL_BIN("start_WHILE", node);
    
    POP_(RAX);
    TEST_RR_(AL, AL);
    JMP_BIN(0x84, "end_WHILE", node);
}

void Do_S_MEMGET(const Node_t *node)
{
    assert(node);

    POP_(RBX);
    LEA_LABEL_(RCX, "vmem_buf");
    ADD_RR_(RCX, RBX);

    MOV_RM_(RAX, RCX, 0);
    AND_RI_(RAX, 0xFF);

    PUSH_(RAX);
}

void Do_S_MEMSET (const Node_t *node)
{
    assert(node);

    POP_(RBX);
    POP_(RAX);
    LEA_LABEL_(RCX, "vmem_buf");
    ADD_RR_(RCX, RBX);
    MOV_MR_(RCX, 0, AL);
}

void Do_S_PRINT (const Node_t *node)
{
    assert(node);

    LEA_LABEL_(RDI, "fmt_int");
    POP_(RAX);
    MOV_RR_(RSI, RAX);
    XOR_RR_(RAX, RAX);
    // TODO: BIN_CALL for printf with PLT
    CALL_("printf WRT ..plt");
}

void Do_S_SCAN (const Node_t *node)
{
    assert(node);

    // TODO: BIN_CALL for scanf with PLT
    CALL_("my_scanf WRT ..plt");
    MOV_MR_OFS_(GetVarOfs(GetLeft(node)), RAX);
}

void Do_S_VDECL (const Node_t *node)
{
    assert(node);

    if (GetVarScope(GetLeft(node)) == GLOBAL) 
    {
        DATA_("%s dq 0", GetVarName(GetLeft(node)));         
        AddPatch(GetVarName(GetLeft(node)));
    }
}

void Do_S_PRINTCHAR(const Node_t *node)
{
    assert(node);

    POP_(RSI);
    LEA_LABEL_(RDI, "fmt_char");
    XOR_RR_(RAX, RAX);  
    // TODO: BIN_CALL for printf with PLT
    CALL_("printf WRT ..plt");
}