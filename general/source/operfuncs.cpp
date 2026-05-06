#include "generalheaders/operfuncs.h"

void GetAsmAdd     (Node_t *node, FILE *file)
{
    assert(node);
    assert(file);

    TEXT_("ADD");
}     
void GetAsmSub     (Node_t *node, FILE *file)
{
    assert(node);
    assert(file);

    TEXT_("SUB");
}     
void GetAsmMul     (Node_t *node, FILE *file)
{
    assert(node);
    assert(file);

    TEXT_("MUL");
}         
void GetAsmDiv     (Node_t *node, FILE *file)
{
    assert(node);
    assert(file);

    TEXT_("DIV");
}
void GetAsmSqrt    (Node_t *node, FILE *file)
{
    assert(node);
    assert(file);

    TEXT_("SQRT");
}     

void GetAsmSkip    (Node_t *node, FILE *file)
{
    assert(node);
    assert(file);
}

void GetAsmPostIf      (Node_t *node, FILE *file)
{
    assert(node);
    assert(file);

    LBL_("end_if", node);
}

void GetAsmPostElse    (Node_t *node, FILE *file)
{
    assert(node);
    assert(file);

    LBL_("end_else", node);
} 

void GetAsmPostWhile   (Node_t *node, FILE *file)
{
    assert(node);
    assert(file);

    LBL_("end_while", node);
} 

void GetAsmInfixIf      (Node_t *node, FILE *file)
{
    assert(node);
    assert(file);

    if (!IsLogicOp(GetLeft(node)))
    {
        PUSH_(0);
        JMP_("JE", "end_if", node);
    }

    else
    {
        const char *str = GetInvLogOp(GetLeft(node));
        JMP_(str, "end_if", node);
    }
}

void GetAsmInfixElse    (Node_t *node, FILE *file)
{
    assert(node);
    assert(file);

    JMP_("JE", "end_else", node);
} 

void GetAsmInfixWhile   (Node_t *node, FILE *file)
{
    assert(node);
    assert(file);

    if (!IsLogicOp(GetLeft(node)))
    {
        PUSH_(0);
        JMP_("JE", "end_while", node);
    }

    else
    {
        const char *str = GetInvLogOp(GetLeft(node));
        JMP_(str, "end_while", node);
    }
}  

void GetAsmFor     (Node_t *node, FILE *file)
{
    assert(node);
    assert(file);
} 

void GetAsmRet     (Node_t *node, FILE *file)
{
    assert(node);
    assert(file);

    TEXT_("RET");
}  

void GetAsmAssign  (Node_t *node, FILE *file)
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

    TEXT_(";assign end");//func!
}

void GetAsmMemget  (Node_t *node, FILE *file)
{
    assert(node);
    assert(file);

} 

void GetAsmMemset  (Node_t *node, FILE *file)
{
    assert(node);
    assert(file);
}

void GetAsmPrint   (Node_t *node, FILE *file)
{
    assert(node);
    assert(file);

    TEXT_("OUT");
} 

void GetAsmScanf   (Node_t *node, FILE *file)
{
    assert(node);
    assert(file);

    TEXT_("IN");
}     
void GetAsmFDecl   (Node_t *node, FILE *file)
{
    assert(node);
    assert(file);
}     
void GetAsmVDecl   (Node_t *node, FILE *file)
{
    assert(node);
    assert(file);
}     
void GetAsmStrEnd  (Node_t *node, FILE *file)
{
    assert(node);
    assert(file);
}

void PushVar(Node_t *node, FILE *file)
{
    assert(node);
    assert(file);

    
    PUSH_(GetVar(node));
    POPR_("AX");
    PUSHM_("AX"); 
    fprintf(file, ";pushed var [%s]\n", Var_table.data[GetVar(node)].name);
}

void PopVar(Node_t *node, FILE *file)
{
    assert(node);
    assert(file);

    
    PUSH_(GetVar(node));
    POPR_("AX");
    POPM_("AX");
    fprintf(file, ";popped in var [%s]\n", Var_table.data[GetVar(node)].name);
}