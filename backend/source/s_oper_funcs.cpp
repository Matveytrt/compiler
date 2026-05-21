#include "../headers/s_oper_funcs.h"
#include <cassert>
#include <cstdio>


#define HANDLE_BIN_OP(op)                 \
    case OP_##op:                         \
        Emit_Infix_Oper(node, func_name); \
        op##_RR_(RAX, RBX);               \
        break;

#define HANDLE_CMP_OP(name, set_inst, set_op)        \
    case OP_##name:                                  \
        Emit_Infix_Oper(node, func_name);            \
        CMP_RR_(RAX, RBX);                           \
        TEXT_(#set_inst " al");                      \
        BIN_SETCC(set_op, REG_AL);                   \
        MOVZX_RR_(RAX, AL);                          \
        break;

void Emit_SQRT(const Node_t *node)
{
    assert(node);

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
}

void Emit_MEMGET(const Node_t *node)
{
    assert(node);

    LEA_LABEL_(RDX, "vmem_buf");
    ADD_RR_(RDX, RAX);

    MOV_RM_(RAX, RDX, 0);
    AND_RI_(RAX, 0xFF);
}

void Emit_MEMSET (const Node_t *node, char *func_name)
{
    assert(node);
    assert(func_name);


    Translate_AST(GetLeft(GetLeft(node)), func_name);
    PUSH_(RAX);
    Translate_AST(GetRight(GetLeft(node)), func_name);
    LEA_LABEL_(RDX, "vmem_buf");
    ADD_RR_(RDX, RAX);
    POP_(RAX);
    MOV_MR_(RDX, 0, AL);
}

void Emit_PRINT (const Node_t *node)
{
    assert(node);
    CALL_("print WRT ..plt");
}

void Emit_SCAN (const Node_t *node)
{
    assert(node);
    CALL_("my_scanf WRT ..plt");
    MOV_MR_OFS_(GetVarOfs(GetLeft(node)), RAX);
}

void Emit_PRINTCHAR(const Node_t *node)
{
    assert(node);
    CALL_("printchar WRT ..plt");
}

void Emit_VDECL (const Node_t *node)
{
    assert(node);

    if (GetVarScope(GetLeft(node)) == GLOBAL) 
    {
        EmitDataValue(GetVarName(GetLeft(node)), 0);
    }
}

void Emit_Oper(const Node_t *node, char *func_name)
{
    assert(node);
    assert(func_name);

    switch (GetOper(node)) {

        HANDLE_BIN_OP(ADD);
        HANDLE_BIN_OP(SUB);
        HANDLE_BIN_OP(MUL);
        
        case OP_DIV:
            Emit_Infix_Oper(node, func_name);
            CQO_();
            DIV_R_(RBX);
            break;
        case OP_SQRT:
            Emit_SQRT(node);
            break;
        case OP_POW:
            MUL_RR_(RAX, RAX);
            break;

        HANDLE_CMP_OP(EQ, sete, SET_E);
        HANDLE_CMP_OP(NEQ, setne, SET_NE);
        HANDLE_CMP_OP(ABOVE_EQ, setge, SET_GE);
        HANDLE_CMP_OP(BELOW_EQ, setle, SET_LE);
        HANDLE_CMP_OP(BELOW, setl, SET_L);
        HANDLE_CMP_OP(ABOVE, setg, SET_G);

        case OP_NOT:
            NOT_R_(RAX);
            break;
        HANDLE_BIN_OP(AND);
        HANDLE_BIN_OP(OR);

        case OPEN_R_BR:
            break;
        case CLOSE_R_BR:
            break;
        case OPEN_SQ_BR:
            break;
        case CLOSE_SQ_BR:
            break;
        case OPEN_FIG_BR:
            break;
        case CLOSE_FIG_BR:
            break;

        case OP_IF:
            Emit_IF(node, func_name);
            break;
        case OP_ELSE:
            Emit_ELSE(node, func_name);
            break;
        case OP_WHILE:
            Emit_WHILE(node, func_name);
            break;
        case OP_FOR:
            Emit_FOR(node, func_name);
            break;

        case OP_RET:
            Emit_RETURN(node, func_name);
            break;
        case OP_BREAK:
            break;

        case OP_ASSIGN:
            Emit_ASSIGN(node, func_name);
            break;
        case OP_END:
            break;

        case OP_F_DCLR:
            WriteFunc(GetLeft(node));
            break;
        case OP_V_DCLR:
            Emit_VDECL(node);
            break;
        
        case OP_COMMA:
            break;
        case OP_STR_END:
            Translate_AST(GetRight(node), func_name);
            break;

        case OP_PRINT:
            Emit_PRINT(node);
            break;
        case OP_SCAN:
            Emit_SCAN(node);
            break;
        case OP_MEMSET:
            Emit_MEMSET(node, func_name);
            break;
        case OP_MEMGET:
            Emit_MEMGET(node);
            break;
        case OP_PRINTCHAR:
            Emit_PRINTCHAR(node);
            break;
        default:
            break;
    }
}

void Emit_Infix_Oper(const Node_t *node, char *func_name)
{
    assert(node);
    assert(func_name);


    PUSH_(RAX);
    Translate_AST(GetRight(node), func_name);
    MOV_RR_(RBX, RAX);
    POP_(RAX);
}

void Emit_IF(const Node_t *node, char *func_name)
{
    assert(node);
    assert(func_name);

    TEST_RR_(AL, AL);
    JMP_BIN(JCC_JE, jz, "end_IF", node);
    Translate_AST(GetRight(node), func_name);
    Emit_IF_Epilog(node);
}

void Emit_IF_Epilog(const Node_t *node)
{
    assert(node);

    Node_t *else_node = NULL;

    if (GetParent(node) && GetRight(GetParent(node)) && ( else_node = GetLeft(GetRight(GetParent(node))) ) 
        && IsOper(else_node, OP_ELSE)) {
        JMP_BIN_UNCOND("end_ELSE", else_node);
    }

    LBL_BIN("end_IF", node);
}

void Emit_WHILE (const Node_t *node, char *func_name)
{
    assert(node);
    assert(func_name);

    LBL_BIN("start_WHILE", node);
    Translate_AST(GetLeft(node), func_name);
    TEST_RR_(AL, AL);
    JMP_BIN(JCC_JE, jz, "end_WHILE", node);
    Translate_AST(GetRight(node), func_name);
    Emit_WHILE_Epilog(node);
}

void Emit_WHILE_Epilog(const Node_t *node)
{
    assert(node);

    JMP_BIN_UNCOND("start_WHILE", node);
    LBL_BIN("end_WHILE", node);
}

void Emit_FOR(const Node_t *node, char *func_name) 
{
    assert(node);
    assert(func_name);

    MOV_RR_(RCX, RAX);
    LBL_BIN("start_FOR", node);
    Translate_AST(GetRight(node), func_name);
    SUB_RI_(RCX, 1);
    TEST_RR_(RCX, RCX);
    JMP_BIN(JCC_JNE, jnz, "start_FOR", node);
}

void Emit_ELSE(const Node_t *node, char *func_name) 
{
    assert(node);
    assert(func_name);

    Translate_AST(GetRight(node), func_name);
    LBL_BIN("end_ELSE", node);;
}

void Emit_ASSIGN(const Node_t *node, char *func_name)
{
    assert(node);
    assert(func_name);

    Translate_AST(GetRight(node), func_name);

    Node_t *assign_node = (IsOper(GetLeft(node), OP_V_DCLR)) ? GetLeft(GetLeft(node)) : GetLeft(node);

    if (GetVarScope(assign_node) == GLOBAL)
    {
        if (IsOper(GetParent(assign_node), OP_V_DCLR)) 
        { 
            EmitDataValue(GetVarName(assign_node), 0);
        }

        MOV_MR_LABEL_(GetVarName(assign_node), RAX);
    }
    else
    {
        int var_ofs = GetVarOfs(assign_node);
        MOV_MR_OFS_(var_ofs, RAX);
    }
}

void Emit_RETURN(const Node_t *node, char *func_name)
{
    assert(node);
    assert(func_name);

    char _label[_LBL_SIZE_] = "";
    sprintf(_label, "exit_%s", func_name);
    TEXT_("jmp %s", _label);
    AddPatch(_label);
}

