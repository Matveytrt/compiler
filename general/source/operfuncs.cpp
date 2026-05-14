#include "../generalheaders/operfuncs.h"

#define DEF_VM_LABEL(name)                      \
    void Do_VM_##name(Node_t *node, FILE *file) \
    {                                           \
        assert(node);                           \
        assert(file);                           \
        VM_LBL_("end_" #name, node);                   \
    }

DEF_VM_LABEL(IF)
DEF_VM_LABEL(ELSE)
DEF_VM_LABEL(WHILE)

#define DEF_VM_OP(op)                         \
    void Do_VM_##op(Node_t *node, FILE *file) \
    {                                         \
        assert(node);                         \
        assert(file);                         \
        VM_TEXT_(#op);                        \
    }

DEF_VM_OP(ADD)
DEF_VM_OP(SUB)
DEF_VM_OP(MUL)
DEF_VM_OP(DIV)
DEF_VM_OP(SQRT)

void Do_VM_SKIP    (Node_t *node, FILE *file)
{
    assert(node);
    assert(file);
}


void Do_VM_InfixIF      (Node_t *node, FILE *file)
{
    assert(node);
    assert(file);

    if (!IsLogicOp(GetLeft(node)))
    {
        VM_PUSH_(0);
        VM_JMP_("JE", "end_if", node);
    }

    else
    {
        const char *str = GetInvLogOp(GetLeft(node));
        VM_JMP_(str, "end_if", node);
    }
}

void Do_VM_InfixELSE    (Node_t *node, FILE *file)
{
    assert(node);
    assert(file);

    VM_JMP_("JE", "end_else", node);
} 

void Do_VM_InfixWHILE   (Node_t *node, FILE *file)
{
    assert(node);
    assert(file);

    if (!IsLogicOp(GetLeft(node)))
    {
        VM_PUSH_(0);
        VM_JMP_("JE", "end_while", node);
    }

    else
    {
        const char *str = GetInvLogOp(GetLeft(node));
        VM_JMP_(str, "end_while", node);
    }
}  

void DO_VM_FOR     (Node_t *node, FILE *file)
{
    assert(node);
    assert(file);
} 

void DO_VM_RET     (Node_t *node, FILE *file)
{
    assert(node);
    assert(file);

    VM_TEXT_("RET");
}  

void DO_VM_ASSIGN  (Node_t *node, FILE *file)
{
    assert(node);
    assert(file);


    if (IsOper(GetLeft(node), OP_V_DCLR))
    {
        PopVar(GetLeft(GetLeft(node)), file);
    }

    else
    {
        PopVar(GetLeft(node), file);
    }

    VM_TEXT_(";assign end");//func!
}

void Do_VM_MEMGET  (Node_t *node, FILE *file)
{
    assert(node);
    assert(file);

} 

void Do_VM_MEMSET  (Node_t *node, FILE *file)
{
    assert(node);
    assert(file);
}

void Do_VM_Print   (Node_t *node, FILE *file)
{
    assert(node);
    assert(file);

    VM_TEXT_("OUT");
} 

void Do_VM_Scanf   (Node_t *node, FILE *file)
{
    assert(node);
    assert(file);

    VM_TEXT_("IN");
}     

void PushVar(Node_t *node, FILE *file)
{
    assert(node);
    assert(file);

    
    VM_PUSH_(GetVar(node));
    VM_POPR_("AX");
    VM_PUSHM_("AX"); 
    fprintf(file, ";pushed var [%s]\n", Var_table.data[GetVar(node)].name);
}

void PopVar(Node_t *node, FILE *file)
{
    assert(node);
    assert(file);

    
    VM_PUSH_(GetVar(node));
    VM_POPR_("AX");
    VM_POPM_("AX");
    fprintf(file, ";popped in var [%s]\n", Var_table.data[GetVar(node)].name);
}