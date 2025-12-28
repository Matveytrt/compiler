#include "generalheaders/operfuncs.h"

void GetAsmAdd     (Node_t *node, FILE *file)
{
    assert(node);
    assert(file);

    fprintf(file, "ADD\n");
}     
void GetAsmSub     (Node_t *node, FILE *file)
{
    assert(node);
    assert(file);

    fprintf(file, "SUB\n");
}     
void GetAsmMul     (Node_t *node, FILE *file)
{
    assert(node);
    assert(file);

    fprintf(file, "MUL\n");
}         
void GetAsmDiv     (Node_t *node, FILE *file)
{
    assert(node);
    assert(file);

    fprintf(file, "DIV\n");
}
void GetAsmSqrt    (Node_t *node, FILE *file)
{
    assert(node);
    assert(file);

    fprintf(file, "SQRT\n");
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

    fprintf(file, ":end_if_%p\n\n", node);
}

void GetAsmPostElse    (Node_t *node, FILE *file)
{
    assert(node);
    assert(file);

    fprintf(file, ":end_else_%p\n\n", node);
} 

void GetAsmPostWhile   (Node_t *node, FILE *file)
{
    assert(node);
    assert(file);

    fprintf(file, ":end_while_%p\n\n", node);
} 

void GetAsmInfixIf      (Node_t *node, FILE *file)
{
    assert(node);
    assert(file);

    if (!IsLogicOp(GetLeft(node)))
    {
        fprintf(file, "PUSH 0\n");
        fprintf(file, "JE :end_if_%p\n", node);
    }

    else
    {
        const char *str = GetInvLogOp(GetLeft(node));
        fprintf(file, "%s :end_if_%p\n", str, node);
    }
}

void GetAsmInfixElse    (Node_t *node, FILE *file)
{
    assert(node);
    assert(file);

    fprintf(file, "JE :end_else_%p\n", node);
} 

void GetAsmInfixWhile   (Node_t *node, FILE *file)
{
    assert(node);
    assert(file);

    if (!IsLogicOp(GetLeft(node)))
    {
        fprintf(file, "PUSH 0\n");
        fprintf(file, "JE :end_while_%p\n", node);
    }

    else
    {
        const char *str = GetInvLogOp(GetLeft(node));
        fprintf(file, "%s :end_while_%p\n", str, node);
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

    fprintf(file, "RET\n");
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

    fprintf(file, ";assign end\n\n");
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

    fprintf(file, "OUT\n");
} 

void GetAsmScanf   (Node_t *node, FILE *file)
{
    assert(node);
    assert(file);

    fprintf(file, "IN\n");
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

    fprintf(file, "PUSH %d\n", GetVar(node));
    fprintf(file, "POPR AX\n");
    fprintf(file, "PUSHM [AX] ;pushed var [%s]\n", Var_table.data[GetVar(node)].name);
}

void PopVar(Node_t *node, FILE *file)
{
    assert(node);
    assert(file);

    fprintf(file, "PUSH %d\n", GetVar(node));
    fprintf(file, "POPR AX\n");
    fprintf(file, "POPM [AX] ;popped in var [%s]\n", Var_table.data[GetVar(node)].name);
}