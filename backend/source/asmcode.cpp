#include "headers/asmcode.h"

void MakeAsm(Node_t *node, const char *output_file)
{
    assert(node);
    assert(output_file);
    
    FILE *file = fopen(output_file, "w");
    assert(file);

    //FillVarInfo(file, &Var_table, 0);
    PrintAsmCode(node, file);
    
    fclose(file);
}

void FillVarInfo(FILE *file, VarStack_t *stk, int start_index)
{
    assert(file);
    assert(stk);

    for (int index = 0; index < stk->size; index++)
    {
        fprintf(file, "PUSH %d\n", stk->data[start_index + index].value);
        fprintf(file, "PUSH %d\n", start_index + index);
        fprintf(file, "POPR AX\n");
        fprintf(file, "POPM [AX]\n;initialized in ram var [%s]\n", Var_table.data[start_index + index].name);
    }
}

void PrintAsmCode(Node_t *node, FILE *file)
{
    assert(node);
    assert(file);

    if (IsOper(node, OP_F_DCLR))
    {
        PrintFunc(node, file);
        return;
    }

    if (GetLeft(node) && !IsOper(node, OP_ASSIGN))
    {
        PrintAsmCode(GetLeft(node), file);    
    }

    PrintInfixOpers(node, file);

    if (GetRight(node))
    {
        PrintAsmCode(GetRight(node), file);    
    }

    switch (GetType(node))
    {
        case TYPE_OP:
            PrintPostfixOpers(node, file);
            break;

        case TYPE_VAR:
            PushVar(node, file);            
            break;

        case TYPE_NUM:
            fprintf(file, "PUSH %d ;pushed num\n", GetNum(node));
            break;

        case TYPE_UFUNC:
            fprintf(file, "CALL :%s\n\n", Func_table.data[GetFunc(node)].name);
            break;

        case TYPE_ERR:

            break;
        
        default:
            break;
    }
}

void PrintPrefixOpers(Node_t *node, FILE *file)
{
    assert(node);
    assert(file);

    Oper_table[GetOper(node)].ptr_prefix(node, file);

}

void PrintInfixOpers(Node_t *node, FILE *file)
{
    assert(node);
    assert(file);

    Oper_table[GetOper(node)].ptr_infix(node, file);
}

void PrintPostfixOpers(Node_t *node, FILE *file)
{
    assert(node);
    assert(file);
    
    Oper_table[GetOper(node)].ptr_postix(node, file);
}

void PrintFunc(Node_t *node, FILE *file)
{
    assert(node);
    assert(file);

    Node_t *func_node = GetLeft(node);
    fprintf(file, ":%s\n", Func_table.data[GetFunc(func_node)].name);

    FillFuncArgs(GetLeft(func_node), file);
    PrintAsmCode(GetRight(func_node), file);
}

void FillFuncArgs(Node_t *node, FILE *file)
{
    assert(node);
    assert(file);

    if (GetLeft(node))
    {
        FillFuncArgs(GetLeft(node), file);
    }

    if (GetRight(node))
    {
        FillFuncArgs(GetRight(node), file);
    }

    if (IsVarType(node))
    {
        PopVar(node, file);
    }
}